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
		//Reco info
		vector<float>   *TrackStartX;
		vector<float>   *TrackStartY;
		vector<float>   *TrackStartZ;
		vector<float>   *TrackStartPX;
		vector<float>   *TrackStartPY;
		vector<float>   *TrackStartPZ;
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
		TBranch        *b_TrackStartX;   //!
		TBranch        *b_TrackStartY;   //!
		TBranch        *b_TrackStartZ;   //!
		TBranch        *b_TrackStartPX;   //!
		TBranch        *b_TrackStartPY;   //!
		TBranch        *b_TrackStartPZ;   //!
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
			TrackStartX = 0;
			TrackStartY = 0;
			TrackStartZ = 0;
			TrackStartPX = 0;
			TrackStartPY = 0;
			TrackStartPZ = 0;
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
			inT->SetBranchAddress("TrackStartX", &TrackStartX, &b_TrackStartX);
			inT->SetBranchAddress("TrackStartY", &TrackStartY, &b_TrackStartY);
			inT->SetBranchAddress("TrackStartZ", &TrackStartZ, &b_TrackStartZ);
			inT->SetBranchAddress("TrackStartPX", &TrackStartPX, &b_TrackStartPX);
			inT->SetBranchAddress("TrackStartPY", &TrackStartPY, &b_TrackStartPY);
			inT->SetBranchAddress("TrackStartPZ", &TrackStartPZ, &b_TrackStartPZ);
			inT->SetBranchAddress("VertX", &VertX, &b_VertX);
			inT->SetBranchAddress("VertY", &VertY, &b_VertY);
			inT->SetBranchAddress("VertZ", &VertZ, &b_VertZ);
			inT->SetBranchAddress("VertN", &VertN, &b_VertN);
		}
};
