//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Oct 28 12:16:40 2020 by ROOT version 6.22/02
// from TTree tree/Vjezbe_4
// found on file: Analysis.root
//////////////////////////////////////////////////////////

#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>

// Header file for the classes stored in the TTree if any.
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Analyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           numberOfEvents;
   string          *nameParticle1;
   Double_t        px1;
   Double_t        py1;
   Double_t        pz1;
   Double_t        pt1;
   Double_t        E1;
   string          *nameParticle2;
   Double_t        px2;
   Double_t        py2;
   Double_t        pz2;
   Double_t        pt2;
   Double_t        E2;

   // List of branches
   TBranch        *b_numberOfEvents;   //!
   TBranch        *b_nameParticle1;   //!
   TBranch        *b_px1;   //!
   TBranch        *b_py1;   //!
   TBranch        *b_pz1;   //!
   TBranch        *b_pt1;   //!
   TBranch        *b_E1;   //!
   TBranch        *b_nameParticle2;   //!
   TBranch        *b_px2;   //!
   TBranch        *b_py2;   //!
   TBranch        *b_pz2;   //!
   TBranch        *b_pt2;   //!
   TBranch        *b_E2;   //!

   Analyzer(TTree *tree=0);
   virtual ~Analyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void PlotHistogram();
};

#endif

#ifdef Analyzer_cxx
Analyzer::Analyzer(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Analysis.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Analysis.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

Analyzer::~Analyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Analyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   nameParticle1 = 0;
   nameParticle2 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("numberOfEvents", &numberOfEvents, &b_numberOfEvents);
   fChain->SetBranchAddress("nameParticle1", &nameParticle1, &b_nameParticle1);
   fChain->SetBranchAddress("px1", &px1, &b_px1);
   fChain->SetBranchAddress("py1", &py1, &b_py1);
   fChain->SetBranchAddress("pz1", &pz1, &b_pz1);
   fChain->SetBranchAddress("pt1", &pt1, &b_pt1);
   fChain->SetBranchAddress("E1", &E1, &b_E1);
   fChain->SetBranchAddress("nameParticle2", &nameParticle2, &b_nameParticle2);
   fChain->SetBranchAddress("px2", &px2, &b_px2);
   fChain->SetBranchAddress("py2", &py2, &b_py2);
   fChain->SetBranchAddress("pz2", &pz2, &b_pz2);
   fChain->SetBranchAddress("pt2", &pt2, &b_pt2);
   fChain->SetBranchAddress("E2", &E2, &b_E2);
   Notify();
}

Bool_t Analyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}


#endif // #ifdef Analyzer_cxx
