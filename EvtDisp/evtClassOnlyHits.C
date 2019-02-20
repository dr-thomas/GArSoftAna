#include <vector>

#include <TTree.h>

class garEvt {
	public:

		//Reco info
		vector<float>   *HitX;
		vector<float>   *HitY;
		vector<float>   *HitZ;
		vector<float>   *HitSig;
		vector<float>   *HitRMS;

		// List of branches

		TBranch        *b_HitX;   //!
		TBranch        *b_HitY;   //!
		TBranch        *b_HitZ;   //!
		TBranch        *b_HitSig;   //!
		TBranch        *b_HitRMS;   //!

		garEvt() {

			HitX = 0;
			HitY = 0;
			HitZ = 0;
			HitSig = 0;
			HitRMS = 0;
		}
		~garEvt() {
		}

		void SetBranchAddresses(TTree* inT) {

			inT->SetMakeClass(1);

			inT->SetBranchAddress("HitX", &HitX, &b_HitX);
			inT->SetBranchAddress("HitY", &HitY, &b_HitY);
			inT->SetBranchAddress("HitZ", &HitZ, &b_HitZ);
			inT->SetBranchAddress("HitSig", &HitSig, &b_HitSig);
			inT->SetBranchAddress("HitRMS", &HitRMS, &b_HitRMS);
		}
};
