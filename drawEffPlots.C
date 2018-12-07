#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TDirectory.h>

#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TMath.h>
#include <TStyle.h>

#include "./evtClass.C"

void drawEffPlots(float searchRadSqrd=100.) {

	TFile* inF = new TFile("./largeBeamAnatree.root", "OPEN");
	if(!inF){
		cout << "Falied to load input file, exiting" << endl;
		return;
	}
	TDirectory* inDir = (TDirectory*)inF->Get("anatree");
	if(!inDir){
		cout << "Falied to load input directory, exiting" << endl;
		return;
	}
	TTree* inT = (TTree*)inDir->Get("GArAnaTree");
	if(!inT){
		cout << "Falied to load input tree, exiting" << endl;
		return;
	}

	garEvt* gEvt = new garEvt();
	gEvt->SetBranchAddresses(inT);

	int searchRad = TMath::Sqrt(searchRadSqrd);

	Float_t posBins[3][3] = {
		//{-274.,274.,0.}, TODO: need to populate in x more
		{-100.,100.,0.},
		{81.,355.,0.},
		{994.,1254,0.}
	};
	float binSize=50.;
	for(int ii=0; ii<3; ii++){
		posBins[ii][2] = (posBins[ii][1]-posBins[ii][0])/binSize;
	}

	TH2F* trueHistXY = new TH2F("trueHistXY","",(int)posBins[0][2],posBins[0][0],posBins[0][1],(int)posBins[1][2],posBins[1][0],posBins[1][1]);
	TH2F* recoHistXY = new TH2F("recoHistXY","",(int)posBins[0][2],posBins[0][0],posBins[0][1],(int)posBins[1][2],posBins[1][0],posBins[1][1]);

	TH2F* trueHistXZ = new TH2F("trueHistXZ","",(int)posBins[0][2],posBins[0][0],posBins[0][1],(int)posBins[2][2],posBins[2][0],posBins[2][1]);
	TH2F* recoHistXZ = new TH2F("recoHistXZ","",(int)posBins[0][2],posBins[0][0],posBins[0][1],(int)posBins[2][2],posBins[2][0],posBins[2][1]);

	TH2F* trueHistYZ = new TH2F("trueHistYZ","",(int)posBins[1][2],posBins[1][0],posBins[1][1],(int)posBins[2][2],posBins[2][0],posBins[2][1]);
	TH2F* recoHistYZ = new TH2F("recoHistYZ","",(int)posBins[1][2],posBins[1][0],posBins[1][1],(int)posBins[2][2],posBins[2][0],posBins[2][1]);

	for(int iEntry=0; iEntry<inT->GetEntries(); iEntry++){
		inT->GetEntry(iEntry);
		if(gEvt->CCNC->at(0)!=0) continue;
		if(std::abs(gEvt->PDG->at(0))!=13) continue;
		trueHistXY->Fill(gEvt->MCPStartX->at(0),gEvt->MCPStartY->at(0));
		trueHistXZ->Fill(gEvt->MCPStartX->at(0),gEvt->MCPStartZ->at(0));
		trueHistYZ->Fill(gEvt->MCPStartY->at(0),gEvt->MCPStartZ->at(0));
		//compare all vertecies locations to ??primary?? track start position 
		for(uint ii=0; ii<gEvt->VertN->size(); ii++){
			float diffSqrd=(gEvt->VertX->at(ii) - gEvt->MCPStartX->at(0))*(gEvt->VertX->at(ii) - gEvt->MCPStartX->at(0));
			diffSqrd+=(gEvt->VertY->at(ii) - gEvt->MCPStartY->at(0))*(gEvt->VertY->at(ii) - gEvt->MCPStartY->at(0));
			diffSqrd+=(gEvt->VertZ->at(ii) - gEvt->MCPStartZ->at(0))*(gEvt->VertZ->at(ii) - gEvt->MCPStartZ->at(0));
			if(diffSqrd>searchRadSqrd) continue;
			recoHistXY->Fill(gEvt->MCPStartX->at(0),gEvt->MCPStartY->at(0));
			recoHistXZ->Fill(gEvt->MCPStartX->at(0),gEvt->MCPStartZ->at(0));
			recoHistYZ->Fill(gEvt->MCPStartY->at(0),gEvt->MCPStartZ->at(0));
			break;
		}
	}

	gStyle->SetOptStat(0);

	TCanvas* c = new TCanvas("can", "can", 2800, 1500);
    TPad* subPad = new TPad("pad", "pad", 0.1, 0.1, 1.0, 1.0);
    subPad->Divide(3, 2, 0.01, 0.01);
    subPad->Draw();

	trueHistXY->GetXaxis()->SetTitle("x (cm)");
	trueHistXY->GetYaxis()->SetTitle("y (cm)");
	recoHistXY->GetXaxis()->SetTitle("x (cm)");
	recoHistXY->GetYaxis()->SetTitle("y (cm)");

	trueHistXZ->GetXaxis()->SetTitle("x (cm)");
	trueHistXZ->GetYaxis()->SetTitle("z (cm)");
	recoHistXZ->GetXaxis()->SetTitle("x (cm)");
	recoHistXZ->GetYaxis()->SetTitle("z (cm)");

	trueHistYZ->GetXaxis()->SetTitle("y (cm)");
	trueHistYZ->GetYaxis()->SetTitle("z (cm)");
	recoHistYZ->GetXaxis()->SetTitle("y (cm)");
	recoHistYZ->GetYaxis()->SetTitle("z (cm)");

	subPad->cd(1);
	trueHistXY->Draw("colz");
	subPad->cd(2);
	trueHistXZ->Draw("colz");
	subPad->cd(3);
	trueHistYZ->Draw("colz");
	subPad->cd(4);
	recoHistXY->Draw("colz");
	subPad->cd(5);
	recoHistXZ->Draw("colz");
	subPad->cd(6);
	recoHistYZ->Draw("colz");

	c->Print("~/Desktop/HgTPCvtxSlices.png");

	c = new TCanvas("can", "can", 2800, 750);
    subPad = new TPad("pad", "pad", 0.01, 0.1, 1.0, 1.0);
    subPad->Divide(3, 1, 0.01, 0.01);
    subPad->Draw();

	recoHistXY->Divide(trueHistXY);
	recoHistXZ->Divide(trueHistXZ);
	recoHistYZ->Divide(trueHistYZ);

	subPad->cd(3);
	recoHistYZ->Draw("colz");
	subPad->cd(2);
	recoHistXZ->Draw("colz");
	subPad->cd(1);
	recoHistXY->Draw("colz");

	c->Print("~/Desktop/HgTPCeffSlices.png");

	inF->Close();
}
