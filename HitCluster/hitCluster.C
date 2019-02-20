#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TStyle.h>
#include <TLatex.h>

#include "./evtClass.C"

/* TODO:
 *      
 *      - Clean up this and parent directory, git commit
 *      - Truth Match tracks .... not yet .... 
 */

void hitCluster() {

	TFile* inF = new TFile("./rootFiles/anatree_0000.root", "OPEN");
	if(!inF){
		cout << "Falied to load input file, exiting" << endl;
		return;
	}
	TDirectory* dir = (TDirectory*)inF->Get("anatree");
	if(!dir) return;
	TTree* inT = (TTree*)dir->Get("GArAnaTree");
	//TTree* inT = (TTree*)inF->Get("GArAnaTree");
	if(!inT) return;

	garEvt* gEvt = new garEvt();
	gEvt->SetBranchAddresses(inT);

	Float_t posBins[3][3] = {
		//x
		{-274.,274.,0.},
		//{-230.,-30.,0.},
		//{30.,230.,0.},
		//{-230,230.,0.},
		//y
		//{81.,355.,0.},
		{-200,200.,0.},
		//{-130,130.,0.},
		//z
		//{994.,1254,0.}
		{-200,200,0.}
		//{-130,130.,0.},
	};

	float binSize=20.;
	for(int ii=0; ii<3; ii++){
		posBins[ii][2] = (posBins[ii][1]-posBins[ii][0])/binSize;
	}

	TH2F* vtxResX = new TH2F("vtxResX","x Residuals",(int)posBins[0][2],posBins[0][0],posBins[0][1],100,-1,1);
	TH2F* vtxResY = new TH2F("vtxResY","y Residuals",(int)posBins[1][2],posBins[1][0],posBins[1][1],100,-1,1);
	TH2F* vtxResZ = new TH2F("vtxResZ","z Residuals",(int)posBins[2][2],posBins[2][0],posBins[2][1],100,-1,1);

	TH1F* totalResX = new TH1F("totalResX","",200,-1,1);
	TH1F* totalResY = new TH1F("totalResY","",200,-1,1);
	TH1F* totalResZ = new TH1F("totalResZ","",200,-1,1);
	for(int iEntry=0; iEntry<inT->GetEntries(); iEntry++){
		if(iEntry%((inT->GetEntries())/10)==0) cout << iEntry*100./(inT->GetEntries()) << "%" << endl;
		inT->GetEntry(iEntry);
		if(gEvt->CCNC->at(0)!=0) continue;
		if(std::abs(gEvt->PDG->at(0))!=13) continue;
		for(uint iTrk=0; iTrk<gEvt->TrackStartX->size(); iTrk++){
			int trajIndex = -1;
			float minDiffSqrd = 555e10;
			for(uint iTraj=0; iTraj<gEvt->MCPStartX->size(); iTraj++){
				float diffSqrd = 1.;
				diffSqrd *= (gEvt->TrackStartX->at(iTrk) - gEvt->MCPStartX->at(iTraj));
				diffSqrd *= (gEvt->TrackStartY->at(iTrk) - gEvt->MCPStartY->at(iTraj));
				diffSqrd *= (gEvt->TrackStartZ->at(iTrk) - gEvt->MCPStartZ->at(iTraj));
				if(diffSqrd<minDiffSqrd) {
					minDiffSqrd = diffSqrd;
					trajIndex = iTraj;
				}
			}
			for(uint iHit=0; iHit<gEvt->TrkHitTrkIndex->size(); iHit++){
				if(gEvt->TrkHitTrkIndex->at(iHit) != iTrk) continue;
			}// for hits
		}// for tracks 
	}

	gStyle->SetTextFont(42);

	TCanvas* c = new TCanvas("can", "can", 2800, 1500);

    TPad* subPad = new TPad("pad", "pad", 0.0, 0.0, 1.0, 1.0);
    subPad->Divide(3, 2, 0.01, 0.01);
    subPad->Draw();

	vtxResX->GetXaxis()->SetTitle("x (cm)");
	vtxResX->GetYaxis()->SetTitle("min. residual (cm)");
	vtxResY->GetXaxis()->SetTitle("y (cm)");
	vtxResY->GetYaxis()->SetTitle("min. residual (cm)");
	vtxResZ->GetXaxis()->SetTitle("z (cm)");
	vtxResZ->GetYaxis()->SetTitle("min. residual (cm)");

	vtxResX->SetStats(0);
	vtxResY->SetStats(0);
	vtxResZ->SetStats(0);

	subPad->cd(3);
	vtxResZ->Draw("colz");
	subPad->cd(2);
	vtxResY->Draw("colz");
	subPad->cd(1);
	vtxResX->Draw("colz");

	totalResX->GetXaxis()->SetTitle("min. x residual (cm)");
	totalResY->GetXaxis()->SetTitle("min. y residual (cm)");
	totalResZ->GetXaxis()->SetTitle("min. z residual (cm)");

	subPad->cd(4);
	totalResX->Draw();
	subPad->cd(5);
	totalResY->Draw();
	subPad->cd(6);
	totalResZ->Draw();

	TString printStr = "~/Desktop/HgTPChitClusterRes.png";
	c->Print(printStr);

	inF->Close();
}
