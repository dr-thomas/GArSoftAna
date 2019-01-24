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

	TH1F* totalResX = new TH1F("totalResX","",200,-200,200);
	TH1F* totalResY = new TH1F("totalResY","",200,-200,200);
	TH1F* totalResZ = new TH1F("totalResZ","",200,-1,1);
	for(int iEntry=0; iEntry<inT->GetEntries(); iEntry++){
		if(iEntry%((inT->GetEntries())/10)==0) cout << iEntry*100./(inT->GetEntries()) << "%" << endl;
		inT->GetEntry(iEntry);
		if(gEvt->CCNC->at(0)!=0) continue;
		if(std::abs(gEvt->PDG->at(0))!=13) continue;
		cout << "event: " << iEntry << endl;
		for(uint ii=0; ii<gEvt->TrackHitX->size(); ii++){
			for(uint jj=0; jj<gEvt->TrackHitX->at(ii).size(); jj++){
				float hitX = gEvt->TrackHitX->at(ii).at(jj);
				if(TMath::Abs(hitX)<1e-6) continue;
				if(TMath::Abs(hitX)>1e9) continue;
				totalResX->Fill(hitX);
			}
			for(uint jj=0; jj<gEvt->TrajHitX->at(ii).size(); jj++){
				float hitX = gEvt->TrajHitX->at(ii).at(jj);
				if(TMath::Abs(hitX)<1e-6) continue;
				if(TMath::Abs(hitX)>1e9) continue;
				totalResY->Fill(hitX);
			}

		}
	}

	TCanvas* c = new TCanvas;
	totalResX->Draw();
	c->Print("~/Desktop/test.eps");

	c = new TCanvas;
	totalResY->Draw();
	c->Print("~/Desktop/test2.eps");
	 

	inF->Close();
}
