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

void drawEffPlots(float searchRadSqrd=1.) {

	TFile* inF = new TFile("./rootFiles/anaMerged.root", "OPEN");
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
		//x
		{-274.,274.,0.},
		//y
		{-250,250.,0.},
		//z
		//{994.,1254,0.}
		{-250,250,0.}
		//{-130,130.,0.},
	};

	/*
	Float_t posBins[3][3] = {
		{-120.,130.,0.},
		{70.,340.,0.},
		{950.,1450,0.}
	};
	*/

	float binSize=10.;
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
		if(iEntry%((inT->GetEntries())/10)==0) cout << iEntry*100./(inT->GetEntries()) << "%" << endl;
		inT->GetEntry(iEntry);

		if(gEvt->CCNC->at(0)!=0) continue;
		if(std::abs(gEvt->PDG->at(0))!=13) continue;
		if(!gEvt->isVertFV(230,10,230)) continue;

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
	gStyle->SetTextFont(42);

	TCanvas* c = new TCanvas("can", "can", 2800, 1500);

	TLatex xText1(0.2,0.955,"X-Y");
	TLatex xText2(0.515,0.955,"X-Z");
	TLatex xText3(0.83,0.955,"Y-Z");
	xText1.Draw();
	xText2.Draw();
	xText3.Draw();

	TLatex yText1(0.03,0.65,"True");
	TLatex yText2(0.03,0.2,"Reco");
	yText1.SetTextAngle(90);
	yText2.SetTextAngle(90);
	yText1.Draw();
	yText2.Draw();

    TPad* subPad = new TPad("pad", "pad", 0.05, 0.0, 1.0, 0.95);
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

	TString printStr = "~/Desktop/HgTPCvtxSlices";
	printStr += searchRad;
	printStr += ".png";

	c->Print(printStr);

	c = new TCanvas("can", "can", 2800, 750);

	TString latexStr = "#delta=";
	latexStr += searchRad;
	latexStr += "cm";
	TLatex yText3(0.02,0.5,latexStr);
	yText3.SetTextAngle(90);
	yText3.Draw();

    subPad = new TPad("pad", "pad", 0.02, 0.1, 1.0, 1.0);
    subPad->Divide(3, 1, 0.01, 0.01);
    subPad->Draw();

	recoHistXY->Divide(trueHistXY);
	recoHistXZ->Divide(trueHistXZ);
	recoHistYZ->Divide(trueHistYZ);

	float nMinForEff=10.;

	//XY
	for(int ii=0; ii<((int)posBins[0][2]); ii++){
		for(int jj=0; jj<((int)posBins[1][2]); jj++){
			if(trueHistXY->GetBinContent(ii+1,jj+1) < nMinForEff) {
				recoHistXY->SetBinContent(ii+1,jj+1,-1.);
			}
		}
	}
	//XZ
	for(int ii=0; ii<((int)posBins[0][2]); ii++){
		for(int jj=0; jj<((int)posBins[2][2]); jj++){
			if(trueHistXZ->GetBinContent(ii+1,jj+1) < nMinForEff) {
				recoHistXZ->SetBinContent(ii+1,jj+1,-1.);
			}
		}
	}
	//YZ
	for(int ii=0; ii<((int)posBins[1][2]); ii++){
		for(int jj=0; jj<((int)posBins[2][2]); jj++){
			if(trueHistYZ->GetBinContent(ii+1,jj+1) < nMinForEff) {
				recoHistYZ->SetBinContent(ii+1,jj+1,-1.);
			}
		}
	}

	recoHistXY->SetMinimum(0.);
	recoHistXY->SetMaximum(1.);
	recoHistXZ->SetMinimum(0.);
	recoHistXZ->SetMaximum(1.);
	recoHistYZ->SetMinimum(0.);
	recoHistYZ->SetMaximum(1.);

	subPad->cd(3);
	recoHistYZ->Draw("colz");
	subPad->cd(2);
	recoHistXZ->Draw("colz");
	subPad->cd(1);
	recoHistXY->Draw("colz");

	printStr = "~/Desktop/HgTPCeffSlices";
	printStr += searchRad;
	printStr += ".png";

	c->Print(printStr);

	inF->Close();
}
