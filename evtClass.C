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

		garEvt() {
		}
		~garEvt() {
		}

		void SetBranchAddresses(TTree* inT) {
			inT->SetBranchAddress("NType", &NType);
			inT->SetBranchAddress("CCNC", &CCNC);
			inT->SetBranchAddress("PDG", &PDG);
			inT->SetBranchAddress("MCPStartX", &MCPStartX);
			inT->SetBranchAddress("MCPStartY", &MCPStartY);
			inT->SetBranchAddress("MCPStartZ", &MCPStartZ);
			inT->SetBranchAddress("MCPPX", &MCPPX);
			inT->SetBranchAddress("MCPPY", &MCPPY);
			inT->SetBranchAddress("MCPPZ", &MCPPZ);
			inT->SetBranchAddress("TrackStartX", &TrackStartX);
			inT->SetBranchAddress("TrackStartY", &TrackStartY);
			inT->SetBranchAddress("TrackStartZ", &TrackStartZ);
			inT->SetBranchAddress("TrackStartPX", &TrackStartPX);
			inT->SetBranchAddress("TrackStartPY", &TrackStartPY);
			inT->SetBranchAddress("TrackStartPZ", &TrackStartPZ);
			inT->SetBranchAddress("VertX", &VertX);
			inT->SetBranchAddress("VertY", &VertY);
			inT->SetBranchAddress("VertZ", &VertZ);
			inT->SetBranchAddress("VertN", &VertN);
		}
};
