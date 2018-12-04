#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TDirectory.h>

#include <TCanvas.h>
#include <TH1F.h>
#include <TMath.h>

#include "./evtClass.C"

void findCloseVtxs() {

	TFile* inF = new TFile("anatree.root", "OPEN");
	if(!inF){
		cout << "Falied to load input file, exiting" << endl;
		return;
	}
	TDirectory* inDir = (TDirectory*)inF->Get("anatree.root:/anatree");
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

	float searchRadSqrd = 150.;
	int searchRad = TMath::Sqrt(searchRadSqrd);

	TString foundVtxsTitleStr = "Number of Vertecies: #delta < ";
	foundVtxsTitleStr += searchRad;
	foundVtxsTitleStr += "cm";

	TH1F* foundVtxsHist = new TH1F("foundVtxsHist", foundVtxsTitleStr,10,0,10);

	for(int iEntry=0; iEntry<inT->GetEntries(); iEntry++){
		inT->GetEntry(iEntry);
		if(gEvt->CCNC->at(0)!=0) continue;
		if(std::abs(gEvt->PDG->at(0))!=13) continue;
		//compare all vertecies locations to ??primary?? track start position 
		float foundVtxs=0.;
		for(uint ii=0; ii<gEvt->VertN->size(); ii++){
			float diffSqrd=(gEvt->VertX->at(ii) - gEvt->MCPStartX->at(0))*(gEvt->VertX->at(ii) - gEvt->MCPStartX->at(0));
			diffSqrd+=(gEvt->VertY->at(ii) - gEvt->MCPStartY->at(0))*(gEvt->VertY->at(ii) - gEvt->MCPStartY->at(0));
			diffSqrd+=(gEvt->VertZ->at(ii) - gEvt->MCPStartZ->at(0))*(gEvt->VertZ->at(ii) - gEvt->MCPStartZ->at(0));
			if(diffSqrd>searchRadSqrd) continue;
			foundVtxs+=1.0;
		}
		foundVtxsHist->Fill(foundVtxs);
	}

	TCanvas* c = new TCanvas();
	foundVtxsHist->Draw();
	c->Print("~/Desktop/foundVtxs.pdf");

	inF->Close();
}
