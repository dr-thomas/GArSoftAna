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

	TH1F* totalResX = new TH1F("totalResX","",200,-1,1);
	TH1F* totalResY = new TH1F("totalResY","",200,-1,1);
	TH1F* totalResZ = new TH1F("totalResZ","",200,-1,1);
	for(int iEntry=0; iEntry<inT->GetEntries(); iEntry++){
		if(iEntry%((inT->GetEntries())/10)==0) cout << iEntry*100./(inT->GetEntries()) << "%" << endl;
		inT->GetEntry(iEntry);
		if(gEvt->CCNC->at(0)!=0) continue;
		if(std::abs(gEvt->PDG->at(0))!=13) continue;
		for(uint iTrk=0; iTrk<gEvt->TrackHitX->size(); iTrk++){
			if(gEvt->TrackHitX->at(iTrk).size() < 10) continue;

			for(uint jTrk=0; jTrk<gEvt->TrackHitX->at(iTrk).size(); jTrk++){

				float hitX = gEvt->TrackHitX->at(iTrk).at(jTrk);
				float hitY = gEvt->TrackHitY->at(iTrk).at(jTrk);
				float hitZ = gEvt->TrackHitZ->at(iTrk).at(jTrk);

				float minDiff=555e10;
				float closeHitTrj[3] = {-555e10,-555e10,-555e10};

				for(uint iTrj=0; iTrj<gEvt->TrajHitX->size(); iTrj++){
					for(uint jTrj=0; jTrj<gEvt->TrajHitX->at(iTrj).size(); jTrj++){
						float hitTrjX = gEvt->TrajHitX->at(iTrj).at(jTrj);
						float hitTrjY = gEvt->TrajHitY->at(iTrj).at(jTrj);
						float hitTrjZ = gEvt->TrajHitZ->at(iTrj).at(jTrj);
						float tempDiff = (hitX-hitTrjX)*(hitX-hitTrjX);
						tempDiff *= (hitY-hitTrjY)*(hitY-hitTrjY);
						tempDiff *= (hitZ-hitTrjZ)*(hitZ-hitTrjZ);
						if(tempDiff<minDiff){
							minDiff=tempDiff;
							closeHitTrj[0] = hitTrjX;
							closeHitTrj[1] = hitTrjY;
							closeHitTrj[2] = hitTrjZ;
						}
					}
				}
				totalResX->Fill(hitX-closeHitTrj[0]);
				totalResY->Fill(hitY-closeHitTrj[1]);
				totalResZ->Fill(hitZ-closeHitTrj[2]);
			} // hits in tracks
		} // tracks
	}

	TCanvas* c = new TCanvas;
	totalResX->Draw();
	c->Print("~/Desktop/resX.eps");

	c = new TCanvas;
	totalResY->Draw();
	c->Print("~/Desktop/resY.eps");

	c = new TCanvas;
	totalResZ->Draw();
	c->Print("~/Desktop/resZ.eps");

	 

	inF->Close();
}
