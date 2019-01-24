#include <vector>

#include <TTree.h>

class garEvt {
	public:

		//True info
		vector<int>     *NType;
		vector<int>     *CCNC;
		vector<int>     *PDG;
		vector<float>   *MCPStartX;
		vector<float>   *MCPStartY;
		vector<float>   *MCPStartZ;
		vector<float>   *MCPPX;
		vector<float>   *MCPPY;
		vector<float>   *MCPPZ;
		vector<vector<float> > *TrajHitX;
		vector<vector<float> > *TrajHitY;
		vector<vector<float> > *TrajHitZ;

		//Reco info
		vector<float>   *HitX;
		vector<float>   *HitY;
		vector<float>   *HitZ;
		vector<float>   *HitSig;
		vector<float>   *HitRMS;

		vector<float>   *TrackStartX;
		vector<float>   *TrackStartY;
		vector<float>   *TrackStartZ;
		vector<float>   *TrackStartPX;
		vector<float>   *TrackStartPY;
		vector<float>   *TrackStartPZ;
		vector<vector<float> > *TrackHitX;
		vector<vector<float> > *TrackHitY;
		vector<vector<float> > *TrackHitZ;

		vector<float>   *VertX;
		vector<float>   *VertY;
		vector<float>   *VertZ;
		vector<int>     *VertN;

		// List of branches
		TBranch        *b_NType;   //!
		TBranch        *b_CCNC;   //!
		TBranch        *b_PDG;   //!
		TBranch        *b_MCPStartX;   //!
		TBranch        *b_MCPStartY;   //!
		TBranch        *b_MCPStartZ;   //!
		TBranch        *b_MCPPX;   //!
		TBranch        *b_MCPPY;   //!
		TBranch        *b_MCPPZ;   //!
		TBranch        *b_TrajHitX;   //!
		TBranch        *b_TrajHitY;   //!
		TBranch        *b_TrajHitZ;   //!


		TBranch        *b_HitX;   //!
		TBranch        *b_HitY;   //!
		TBranch        *b_HitZ;   //!
		TBranch        *b_HitSig;   //!
		TBranch        *b_HitRMS;   //!

		TBranch        *b_TrackStartX;   //!
		TBranch        *b_TrackStartY;   //!
		TBranch        *b_TrackStartZ;   //!
		TBranch        *b_TrackStartPX;   //!
		TBranch        *b_TrackStartPY;   //!
		TBranch        *b_TrackStartPZ;   //!
		TBranch        *b_TrackHitX;   //!
		TBranch        *b_TrackHitY;   //!
		TBranch        *b_TrackHitZ;   //!

		TBranch        *b_VertX;   //!
		TBranch        *b_VertY;   //!
		TBranch        *b_VertZ;   //!
		TBranch        *b_VertN;   //!


		garEvt() {
			NType = 0;
			CCNC = 0;
			PDG = 0;
			MCPStartX = 0;
			MCPStartY = 0;
			MCPStartZ = 0;
			MCPPX = 0;
			MCPPY = 0;
			MCPPZ = 0;
			TrajHitX = 0;
			TrajHitY = 0;
			TrajHitZ = 0;

			HitX = 0;
			HitY = 0;
			HitZ = 0;
			HitSig = 0;
			HitRMS = 0;
			TrackStartX = 0;
			TrackStartY = 0;
			TrackStartZ = 0;
			TrackStartPX = 0;
			TrackStartPY = 0;
			TrackStartPZ = 0;
			TrackHitX = 0;
			TrackHitY = 0;
			TrackHitZ = 0;
			VertX = 0;
			VertY = 0;
			VertZ = 0;
			VertN = 0;
		}
		~garEvt() {
		}

		void SetBranchAddresses(TTree* inT) {

			inT->SetMakeClass(1);

			inT->SetBranchAddress("NType", &NType, &b_NType);
			inT->SetBranchAddress("CCNC", &CCNC, &b_CCNC);
			inT->SetBranchAddress("PDG", &PDG, &b_PDG);
			inT->SetBranchAddress("MCPStartX", &MCPStartX, &b_MCPStartX);
			inT->SetBranchAddress("MCPStartY", &MCPStartY, &b_MCPStartY);
			inT->SetBranchAddress("MCPStartZ", &MCPStartZ, &b_MCPStartZ);
			inT->SetBranchAddress("MCPPX", &MCPPX, &b_MCPPX);
			inT->SetBranchAddress("MCPPY", &MCPPY, &b_MCPPY);
			inT->SetBranchAddress("MCPPZ", &MCPPZ, &b_MCPPZ);
			inT->SetBranchAddress("TrajHitX", &TrajHitX, &b_TrajHitX);
			inT->SetBranchAddress("TrajHitY", &TrajHitY, &b_TrajHitY);
			inT->SetBranchAddress("TrajHitZ", &TrajHitZ, &b_TrajHitZ);
			inT->SetBranchAddress("HitX", &HitX, &b_HitX);
			inT->SetBranchAddress("HitY", &HitY, &b_HitY);
			inT->SetBranchAddress("HitZ", &HitZ, &b_HitZ);
			inT->SetBranchAddress("HitSig", &HitSig, &b_HitSig);
			inT->SetBranchAddress("HitRMS", &HitRMS, &b_HitRMS);
			inT->SetBranchAddress("TrackStartX", &TrackStartX, &b_TrackStartX);
			inT->SetBranchAddress("TrackStartY", &TrackStartY, &b_TrackStartY);
			inT->SetBranchAddress("TrackStartZ", &TrackStartZ, &b_TrackStartZ);
			inT->SetBranchAddress("TrackStartPX", &TrackStartPX, &b_TrackStartPX);
			inT->SetBranchAddress("TrackStartPY", &TrackStartPY, &b_TrackStartPY);
			inT->SetBranchAddress("TrackStartPZ", &TrackStartPZ, &b_TrackStartPZ);
			inT->SetBranchAddress("TrackHitX", &TrackHitX, &b_TrackHitX);
			inT->SetBranchAddress("TrackHitY", &TrackHitY, &b_TrackHitY);
			inT->SetBranchAddress("TrackHitZ", &TrackHitZ, &b_TrackHitZ);
			inT->SetBranchAddress("VertX", &VertX, &b_VertX);
			inT->SetBranchAddress("VertY", &VertY, &b_VertY);
			inT->SetBranchAddress("VertZ", &VertZ, &b_VertZ);
			inT->SetBranchAddress("VertN", &VertN, &b_VertN);
		}
};
