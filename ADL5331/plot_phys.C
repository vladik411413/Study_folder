void plot_phys(){
	TCanvas *c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(8);
	TGraphErrors *gr = new TGraphErrors();
  TGraph *gr_def = new TGraphErrors();
	fstream file;
	file.open("1.txt",ios::in);
	double Vgain,mV,x,y,dx,dy;
	int n = 0;
	while(1){
		file >> Vgain >> mV;
		n = gr -> GetN();
    y = 20*log10(sqrt(2)*mV/73.0);
		dx = 0.001;
		dy = 0.03*20*73.0/(mV*log(10));
		gr -> SetPoint(n,Vgain,y);
		gr -> SetPointError(n,dx,dy);
		if (file.eof()) break;
	}
  file.close();
  file.open("2.txt",ios::in);
	while(1){
		file >> x >> y;
		n = gr_def -> GetN();

		gr_def -> SetPoint(n,x,y);
		if (file.eof()) break;
	}
  file.close();
	//TAxis *axis = gr1->GetXaxis();
	//axis->SetLimits(0.,5.);                 // along X
	//gr->GetHistogram()->SetMaximum(80);   // along          
	//gr->GetHistogram()->SetMinimum(-5);  //   Y
	gr -> SetMarkerColor(4);
	gr -> SetMarkerStyle(8);
  gr -> SetLineColor(4);
  gr_def -> SetLineColor(2);
	TMultiGraph *mg = new TMultiGraph();
  mg -> SetTitle(Form("ADL5331 (V_{in (pp)}=73 mV, f = 40 MHz);V_{gain},mV;Gain, dB"));
	mg->Add(gr,"APL");
	mg->Add(gr_def,"AC");
	mg->Draw("ap");
	TLegend *leg = new TLegend(0.1, 0.7, 0.3, 0.9);
	leg->AddEntry(gr,"#scale[0.6]{de facto}","PL");
  leg->AddEntry(gr_def,"#scale[0.6]{datasheet}","PL");
	leg->Draw();
  c1->Update();
}
