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

void momRes() {

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
		{-274.,274.,0.},
		{-250,250.,0.},
		{-250,250,0.}
	};
	float binSize=10.;
	for(int ii=0; ii<3; ii++){
		posBins[ii][2] = (posBins[ii][1]-posBins[ii][0])/binSize;
	}

	TH2F* resHist = new TH2F("resHist","",50,0,2000,50,-2,2);

	for(int iEvt=0; iEvt<inT->GetEntries(); iEvt++){
		inT->GetEntry(iEvt);
		if(gEvt->PDG->at(0)!=2212) continue;
		float pMomTrue = 0;
		pMomTrue += (gEvt->MCPPX->at(0))*(gEvt->MCPPX->at(0));
		pMomTrue += (gEvt->MCPPY->at(0))*(gEvt->MCPPY->at(0));
		pMomTrue += (gEvt->MCPPZ->at(0))*(gEvt->MCPPZ->at(0));
		pMomTrue = TMath::Sqrt(pMomTrue);
		cout << gEvt->MCPPX->at(0) << " ";
		cout << gEvt->MCPPY->at(0) << " ";
		cout << gEvt->MCPPZ->at(0) << endl;

		float minDiff = 555e10;
		int bestTrackIndex=-1;
		vector<float> trackMoms;
		for(uint ii=0; ii<gEvt->TrackStartPX->size(); ii++){
			float pMom = 0;
			pMom += (gEvt->TrackStartPX->at(ii))*(gEvt->TrackStartPX->at(ii));
			pMom += (gEvt->TrackStartPY->at(ii))*(gEvt->TrackStartPY->at(ii));
			pMom += (gEvt->TrackStartPZ->at(ii))*(gEvt->TrackStartPZ->at(ii));
			pMom = TMath::Sqrt(pMom);
			trackMoms.push_back(pMom);

			float diff = (pMom-pMomTrue)*(pMom-pMomTrue);
			if(diff<minDiff){
				minDiff = diff;
				bestTrackIndex = ii;
			}
		}
		cout << pMomTrue << endl;
		if(bestTrackIndex>=0){
			resHist->Fill(pMomTrue*1000,(trackMoms.at(bestTrackIndex)-pMomTrue)/pMomTrue);
		}
	}

	TCanvas* c = new TCanvas;
	
	resHist->Draw();

	TString printStr = "~/Desktop/bestTrackRes.png";
	c->Print(printStr);

	inF->Close();
}
