#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TDirectory.h>

#include "./evtClass.C"

void countOffPosMus() {

	//TFile* inF = new TFile("anatree.root", "OPEN");
	TFile* inF = new TFile("./anatreeDiffBeamDir.root", "OPEN");
	if(!inF){
		cout << "Falied to load input file, exiting" << endl;
		return;
	}
	//TDirectory* inDir = (TDirectory*)inF->Get("anatree.root:/anatree");
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

	int nCCwoMu=0;
	for(int iEntry=0; iEntry<inT->GetEntries(); iEntry++){
		inT->GetEntry(iEntry);
		for(int ii=0; ii<(gEvt->PDG->size()); ii++){
			if(gEvt->PDG->at(ii)==13 || gEvt->PDG->at(ii)==-13){
				if(ii>0 && ii<10){
					cout << "found weird one, was it CC?: " << gEvt->CCNC->at(0) << endl;
					if(gEvt->CCNC->at(0)==1) {
						nCCwoMu++;
					}
					for(int jj=0; (jj<(gEvt->PDG->size()) && jj<10); jj++){
						cout << gEvt->PDG->at(jj) << endl;
					}
				}
			}
		}
	}
	cout << "total CC events without muon in primary position: " << nCCwoMu << " out of ";
	cout << inT->GetEntries() << " which is " << nCCwoMu*1.0/(inT->GetEntries()*1.0)*100. << "%" << endl;
	inF->Close();
}
