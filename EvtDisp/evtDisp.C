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

void evtDisp(int eventID=0) {

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

	TH2F* xyHist = new TH2F("xyHist","X-Y",(int)posBins[0][2],posBins[0][0],posBins[0][1],(int)posBins[1][2],posBins[1][0],posBins[1][1]);
	TH2F* xzHist = new TH2F("xzHist","X-Z",(int)posBins[0][2],posBins[0][0],posBins[0][1],(int)posBins[2][2],posBins[2][0],posBins[2][1]);
	TH2F* yzHist = new TH2F("yzHist","Y-Z",(int)posBins[1][2],posBins[1][0],posBins[1][1],(int)posBins[2][2],posBins[2][0],posBins[2][1]);

	inT->GetEntry(eventID);
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

	subPad->cd(3);
	gPad->SetLogz();
	yzHist->Draw("colz");
	subPad->cd(2);
	gPad->SetLogz();
	xzHist->Draw("colz");
	subPad->cd(1);
	gPad->SetLogz();
	xyHist->Draw("colz");

	TString printStr = "~/Desktop/EvtDisp.png";
	c->Print(printStr);

	inF->Close();
}
