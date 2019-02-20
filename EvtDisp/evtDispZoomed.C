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

void evtDispZoomed(int eventID=0) {

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

	float zoomBox[3][2] {
		{555e10,-555e10},
		{555e10,-555e10},
		{555e10,-555e10}
	};
	inT->GetEntry(eventID);
	for(uint ii=0; ii<gEvt->HitX->size(); ii++){
		float pos[3];
		pos[0] = gEvt->HitX->at(ii);
		pos[1] = gEvt->HitY->at(ii);
		pos[2] = gEvt->HitZ->at(ii);

		for(int jj=0; jj<3; jj++){
			if(pos[jj]<zoomBox[jj][0]){
				zoomBox[jj][0] = pos[jj];
			}
			if(pos[jj]>zoomBox[jj][1]){
				zoomBox[jj][1] = pos[jj];
			}
		}
	}

	TH2F* xyHist = new TH2F("xyHist","X-Y",50,zoomBox[0][0],zoomBox[0][1],50,zoomBox[1][0],zoomBox[1][1]);
	TH2F* xzHist = new TH2F("xzHist","X-Z",50,zoomBox[0][0],zoomBox[0][1],50,zoomBox[2][0],zoomBox[2][1]);
	TH2F* yzHist = new TH2F("yzHist","Y-Z",50,zoomBox[1][0],zoomBox[1][1],50,zoomBox[2][0],zoomBox[2][1]);

	for(uint ii=0; ii<gEvt->HitX->size(); ii++){
		xyHist->Fill(gEvt->HitX->at(ii), gEvt->HitY->at(ii),gEvt->HitSig->at(ii));
		xzHist->Fill(gEvt->HitX->at(ii), gEvt->HitZ->at(ii),gEvt->HitSig->at(ii));
		yzHist->Fill(gEvt->HitY->at(ii), gEvt->HitZ->at(ii),gEvt->HitSig->at(ii));
	}

	gStyle->SetTextFont(42);

	TCanvas* c = new TCanvas("can", "can", 2800, 750);

    TPad* subPad = new TPad("pad", "pad", 0.0, 0.0, 1.0, 1.0);
    subPad->Divide(3, 1, 0.01, 0.01);
    subPad->Draw();

	xyHist->SetStats(0);
	xzHist->SetStats(0);
	yzHist->SetStats(0);

	subPad->cd(3);
	yzHist->Draw("colz");
	subPad->cd(2);
	xzHist->Draw("colz");
	subPad->cd(1);
	xyHist->Draw("colz");

	TString printStr = "~/Desktop/EvtDispZoomed.png";
	c->Print(printStr);

	inF->Close();
}
