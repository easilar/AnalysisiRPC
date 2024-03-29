#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TF1.h"

void dqm_beamdump(Int_t hv, Int_t sn , Int_t mt, const char * loc) {
	TString s("");
	s.Form("%s_HV_%d_SN_%d_MaxTrig_%d_Run*.root",loc,hv,sn,mt);
	std::cout<<s<<std::endl;
	//TFile *f1 = TFile::Open(s);
	//TTree *evt = (TTree*)f1->Get("evt");
	TChain ch("evt");
	ch.Add(s);
	gROOT->SetStyle("Plain");
	gROOT->ForceStyle();
	gStyle->SetOptStat(0);
	//Draw bc0 time 
	TCanvas *c1 = new TCanvas("c1","The Ntuple canvas",200,10,780,780);
	TPad *pad1 = new TPad("pad1","This is pad1",0.02,0.02,0.98,0.98,21);
	pad1->UseCurrentStyle();
	pad1->Draw();
	pad1->cd();
	pad1->SetGrid();
	pad1->SetLogy();
	TH1F *hist1= new TH1F("hist1", "bc0 time",100,89624.6,89625.4);
	ch.Draw("m_time(m_traw(frame))>>hist1","(m_channel(frame)==32)");
	std::cout<<"All events / 3: "<< (hist1->Integral())/3 << std::endl;
	hist1->SetLineColor(4);
	hist1->SetLineWidth(2);
	hist1->GetXaxis()->SetTitle("bc0 time [ns]");
	hist1->GetYaxis()->SetTitle("Events");
	hist1->GetYaxis()->SetLabelOffset(0.007);
	hist1->GetYaxis()->SetTitleOffset(1.3);
	hist1->SetLabelSize(0.02,"x");
	hist1->SetTitle("");
	hist1->Draw("Histo");
	c1->cd();
	c1->Update();
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__bc_0.root",hv,sn,mt);
	c1->SaveAs(s);
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__bc_0.pdf",hv,sn,mt);
	c1->SaveAs(s);
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__bc_0_forwebDCS.png",hv,sn,mt);
	c1->SaveAs(s);
	//Draw trigger time
	TCanvas *c2 = new TCanvas("c2","The Ntuple canvas",200,10,780,780);
	TPad *pad2 = new TPad("pad2","This is pad2",0.02,0.02,0.98,0.98,21);
	pad2->UseCurrentStyle();
	pad2->Draw();
	pad2->cd();
	pad2->SetGrid();
	pad2->SetLogy();
	TH1F *hist2= new TH1F("hist2", "trigger time",91000,0,91000);
	ch.Draw("m_time(m_traw(frame))>>hist2","(m_channel(frame)==33)");
	std::cout<<"All triggers /3 : "<< (hist2->Integral())/3 << std::endl;
	hist2->SetLineColor(4);
	hist2->SetLineWidth(2);
	hist2->GetXaxis()->SetTitle("trigger time [ns]");
	hist2->GetYaxis()->SetTitle("Events");
	hist2->GetYaxis()->SetLabelOffset(0.007);
	hist2->GetYaxis()->SetTitleOffset(1.3);
	hist2->SetLabelSize(0.02,"x");
	hist2->SetTitle("");
	hist2->Draw("Histo");
	c2->cd();
	c2->Update();
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__triggerTime.root",hv,sn,mt);
	c2->SaveAs(s);
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__triggerTime.pdf",hv,sn,mt);
	c2->SaveAs(s);
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__triggerTime_forwebDCS.png",hv,sn,mt);
	c2->SaveAs(s);
	//time vs strip	
	TCanvas *c3 = new TCanvas("c3","The Ntuple canvas",200,10,900,780);
	TPad *pad3 = new TPad("pad3","This is pad3",0.02,0.02,0.98,0.98,21);
	pad3->UseCurrentStyle();
	pad3->Draw();
	pad3->cd();
	pad3->SetGrid();
	pad3->SetLogz();
	TH2F *hist3= new TH2F("hist3", "direct strip time",91000,0,91000,50,0,50);
	ch.Draw("m_time(m_traw(frame)):m_strip(frame)>>hist3(48, -0.5, 47.5,76,329.9,345.1)","(m_channel(frame)<32)&&(c_side(m_channel(frame)))<0.5");
	hist3->SetLineColor(4);
	hist3->SetLineWidth(2);
	hist3->GetXaxis()->SetTitle("time stamp");
	hist3->GetYaxis()->SetTitle("Strips");
	hist3->GetYaxis()->SetLabelOffset(0.007);
	hist3->GetYaxis()->SetTitleOffset(1.3);
	hist3->SetLabelSize(0.02,"x");
	hist3->SetTitle("");
	hist3->Draw("COLZ");

	ofstream myfile;
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__2D_timeDirectvsStrip.txt",hv,sn,mt);
	myfile.open (s.Data());
  
	Int_t n = hist3->GetNbinsX();
	Int_t p = hist3->GetNbinsY();
	for (Int_t i=1; i<=n; i++) {
	  for (Int_t j=1; j<=p; j++) {
	    myfile << 
	      hist3->GetXaxis()->GetBinLowEdge(i)+hist3->GetXaxis()->GetBinWidth(i)/2 << " " <<
	      hist3->GetYaxis()->GetBinLowEdge(j)+hist3->GetYaxis()->GetBinWidth(j)/2 << " " <<
	      hist3->GetBinContent(i,j) << "\n";
	  }
	}

	myfile.close();


	

	
	c3->cd();
	c3->Update();
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__2D_timeDirectvsStrip.root",hv,sn,mt);
	c3->SaveAs(s);
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__2D_timevsDirectStrip.pdf",hv,sn,mt);
	c3->SaveAs(s);
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__2D_timevsDirectStrip_forwebDCS.png",hv,sn,mt);
	c3->SaveAs(s);
	// strip vs bc0
	TCanvas *c4 = new TCanvas("c4","The Ntuple canvas",200,10,900,780);
	TPad *pad4 = new TPad("pad4","This is pad4",0.02,0.02,0.98,0.98,21);
	pad4->UseCurrentStyle();
	pad4->Draw();
	pad4->cd();
	pad4->SetGrid();
	pad4->SetLogz();
	pad4->SetRightMargin(0.12);
	TH2F *hist4= new TH2F("hist4", "trigger time",100,0,15,50,0,50);
	ch.Draw("m_strip(frame):(bc0*90*10^(-6))/3600>>hist4","m_channel(frame)<32&&m_time(m_traw(frame))>0");
	hist4->SetLineColor(4);
	hist4->SetLineWidth(2);
	hist4->GetXaxis()->SetTitle("time [hours]");
	hist4->GetYaxis()->SetTitle("Strips");
	hist4->GetYaxis()->SetLabelOffset(0.007);
	hist4->GetYaxis()->SetTitleOffset(1.3);
	hist4->SetLabelSize(0.02,"x");
	hist4->SetTitle("");
	hist4->Draw("COLZ");
	c4->cd();
   	c4->Update();
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__2D_bc0timevsStrips.root",hv,sn,mt);
	c4->SaveAs(s);
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__2D_bc0timevsStrips.pdf",hv,sn,mt);
	c4->SaveAs(s);
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__2D_bc0timevsStrips_forwebDCS.png",hv,sn,mt);
	c4->SaveAs(s);
	//strip vs time ps
	TCanvas *c5 = new TCanvas("c5","The Ntuple canvas",200,10,900,780);
	TPad *pad5 = new TPad("pad5","This is pad5",0.02,0.02,0.98,0.98,21);
	pad5->UseCurrentStyle();
	pad5->Draw();
	pad5->cd();
	pad5->SetGrid();
	//pad5->SetLogz();
	pad5->SetRightMargin(0.12);
	TH2F *hist5= new TH2F("hist5", "Return strip time",180000,-90000,90000,50,0,50);
	ch.Draw("m_time(m_traw(frame)):m_strip(frame)>>hist5(48, -0.5, 47.5,76,329.9,345.1)","(m_channel(frame)<32)&&(c_side(m_channel(frame))>0.1)");
	hist5->SetLineColor(4);
	hist5->SetLineWidth(2);
	hist5->GetXaxis()->SetTitle("time [ns]");
	hist5->GetYaxis()->SetTitle("Strips");
	hist5->GetYaxis()->SetLabelOffset(0.007);
	hist5->GetYaxis()->SetTitleOffset(1.3);
	hist5->SetLabelSize(0.02,"x");
	hist5->SetTitle("");
	hist5->Draw("COLZ");


	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__2D_timeReturnvsStrip.txt",hv,sn,mt);
	myfile.open (s.Data());
  
	n = hist5->GetNbinsX();
	p = hist5->GetNbinsY();

	for (Int_t i=1; i<=n; i++) {
	  for (Int_t j=1; j<=p; j++) {
	    myfile << 
	      hist5->GetXaxis()->GetBinLowEdge(i)+hist5->GetXaxis()->GetBinWidth(i)/2 << " " <<
	      hist5->GetYaxis()->GetBinLowEdge(j)+hist5->GetXaxis()->GetBinWidth(j)/2 << " " <<
	      hist5->GetBinContent(i,j) << "\n";
	  }
	}

	myfile.close();


	

	
	c5->cd();
   	c5->Update();
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__2D_timevsReturnvsStrips.root",hv,sn,mt);
	c5->SaveAs(s);
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__2D_timevsReturnvsStrips.pdf",hv,sn,mt);
	c5->SaveAs(s);
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__2D_timevsReturnvsStrips_forwebDCS.png",hv,sn,mt);
	c5->SaveAs(s);

	//stip hits
	TCanvas *c6 = new TCanvas("c6","The Ntuple canvas",200,10,780,780);
	TPad *pad6 = new TPad("pad6","This is pad6",0.02,0.02,0.98,0.98,21);
	pad6->UseCurrentStyle();
	pad6->Draw();
	pad6->cd();
	pad6->SetGrid();
	pad6->SetLogy();
	TH1F *hist6= new TH1F("hist6", "trigger time",50,0,50);
	ch.Draw("m_strip(frame)>>hist6","(m_channel(frame)<32&&m_time(m_traw(frame))>0)");
	hist6->SetLineColor(4);
	hist6->SetLineWidth(2);
	hist6->GetXaxis()->SetTitle("strips");
	hist6->GetYaxis()->SetTitle("All Hits");
	hist6->GetYaxis()->SetLabelOffset(0.007);
	hist6->GetYaxis()->SetTitleOffset(1.3);
	hist6->SetLabelSize(0.02,"x");
	hist6->SetTitle("");
	hist6->Draw("Histo");
	c6->cd();
	c6->Update();
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__StripsAllhits.root",hv,sn,mt);
	c6->SaveAs(s);
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__StripsAllhits.pdf",hv,sn,mt);
	c6->SaveAs(s);
	s.Form("plots_gif/DQM_plots/_HV_%d_SN_%d_MaxTrig_%d__StripsAllhits_forwebDCS.png",hv,sn,mt);
	c6->SaveAs(s);
	gApplication->Terminate();
	
}
