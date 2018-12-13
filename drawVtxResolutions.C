#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TDirectory.h>

#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TMath.h>
#include <TStyle.h>
#include <TLatex.h>

#include "./evtClass.C"

void drawVtxResolutions(float searchRadSqrd=100.) {

	TFile* inF = new TFile("./rootFiles/anaMergedLarger.root", "OPEN");
	if(!inF){
		cout << "Falied to load input file, exiting" << endl;
		return;
	}
	TTree* inT = (TTree*)inF->Get("GArAnaTree");
	if(!inT){
		cout << "Falied to load input tree, exiting" << endl;
		return;
	}

	garEvt* gEvt = new garEvt();
	gEvt->SetBranchAddresses(inT);

	int searchRad = TMath::Sqrt(searchRadSqrd);

	Float_t posBins[3][3] = {
		{-274.,274.,0.},
		{81.,355.,0.},
		{994.,1254,0.}
	};

	float binSize=20.;
	for(int ii=0; ii<3; ii++){
		posBins[ii][2] = (posBins[ii][1]-posBins[ii][0])/binSize;
	}

	TH2F* vtxResX = new TH2F("vtxResX","x Resoltuion",(int)posBins[0][2],posBins[0][0],posBins[0][1],50,-5,5);
	TH2F* vtxResY = new TH2F("vtxResY","y Resoltuion",(int)posBins[1][2],posBins[1][0],posBins[1][1],50,-5,5);
	TH2F* vtxResZ = new TH2F("vtxResZ","z Resoltuion",(int)posBins[2][2],posBins[2][0],posBins[2][1],50,-5,5);

	TH1F* totalResX = new TH1F("totalResX","",50,-5,5);
	TH1F* totalResY = new TH1F("totalResY","",50,-5,5);
	TH1F* totalResZ = new TH1F("totalResZ","",50,-5,5);

	for(int iEntry=0; iEntry<inT->GetEntries(); iEntry++){
		if(iEntry%((inT->GetEntries())/10)==0) cout << iEntry*100./(inT->GetEntries()) << "%" << endl;
		inT->GetEntry(iEntry);
		if(gEvt->CCNC->at(0)!=0) continue;
		if(std::abs(gEvt->PDG->at(0))!=13) continue;
		//compare all vertecies locations to ??primary?? track start position 
		float minDiffSqrd=1e6;
		float closestVtxPos[3];
		for(uint ii=0; ii<gEvt->VertN->size(); ii++){
			float diffSqrd=(gEvt->VertX->at(ii) - gEvt->MCPStartX->at(0))*(gEvt->VertX->at(ii) - gEvt->MCPStartX->at(0));
			diffSqrd+=(gEvt->VertY->at(ii) - gEvt->MCPStartY->at(0))*(gEvt->VertY->at(ii) - gEvt->MCPStartY->at(0));
			diffSqrd+=(gEvt->VertZ->at(ii) - gEvt->MCPStartZ->at(0))*(gEvt->VertZ->at(ii) - gEvt->MCPStartZ->at(0));
			if(diffSqrd<minDiffSqrd){
				minDiffSqrd=diffSqrd;
				closestVtxPos[0] = gEvt->VertX->at(ii);
				closestVtxPos[1] = gEvt->VertY->at(ii);
				closestVtxPos[2] = gEvt->VertZ->at(ii);
			}
		}
		if(minDiffSqrd>searchRadSqrd) continue;

		vtxResX->Fill(closestVtxPos[0], (closestVtxPos[0]-gEvt->MCPStartX->at(0)));
		totalResX->Fill((closestVtxPos[0]-gEvt->MCPStartX->at(0)));

		vtxResY->Fill(closestVtxPos[1], (closestVtxPos[1]-gEvt->MCPStartY->at(0)));
		totalResY->Fill((closestVtxPos[1]-gEvt->MCPStartY->at(0)));

		vtxResZ->Fill(closestVtxPos[2], (closestVtxPos[2]-gEvt->MCPStartZ->at(0)));
		totalResZ->Fill((closestVtxPos[2]-gEvt->MCPStartZ->at(0)));
	}

	gStyle->SetTextFont(42);

	TCanvas* c = new TCanvas("can", "can", 2800, 1500);

    TPad* subPad = new TPad("pad", "pad", 0.05, 0.0, 1.0, 0.95);
    subPad->Divide(3, 2, 0.01, 0.01);
    subPad->Draw();

	vtxResX->GetXaxis()->SetTitle("x (cm)");
	vtxResX->GetYaxis()->SetTitle("x_{reco} - x_{true}");
	vtxResY->GetXaxis()->SetTitle("y (cm)");
	vtxResY->GetYaxis()->SetTitle("y_{reco} - y_{true}");
	vtxResZ->GetXaxis()->SetTitle("z (cm)");
	vtxResZ->GetYaxis()->SetTitle("z_{reco} - z_{true}");

	vtxResX->SetStats(0);
	vtxResY->SetStats(0);
	vtxResZ->SetStats(0);

	subPad->cd(3);
	vtxResZ->Draw("colz");
	subPad->cd(2);
	vtxResY->Draw("colz");
	subPad->cd(1);
	vtxResX->Draw("colz");

	totalResX->GetXaxis()->SetTitle("x_{reco} - x_{true}");
	totalResY->GetXaxis()->SetTitle("y_{reco} - y_{true}");
	totalResZ->GetXaxis()->SetTitle("z_{reco} - z_{true}");

	subPad->cd(4);
	totalResX->Draw();
	subPad->cd(5);
	totalResY->Draw();
	subPad->cd(6);
	totalResZ->Draw();

	TString printStr = "~/Desktop/HgTPCvtxRes.png";
	c->Print(printStr);

	inF->Close();
}
