void plot_phys(){
	TCanvas *c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(8);
	TGraphErrors *gr = new TGraphErrors();
	fstream file;
	file.open("Ne.txt",ios::in);
	double x,y,dx,dy;
	int n = 0;
	while(1){
		file >> y >> x;
		n = gr -> GetN();
		dy = y*0.02 + 2;
		dx = x*0.012 + 2;
		gr -> SetPoint(n,x,y);
		gr -> SetPointError(n,dx,dy);
		if (file.eof()) break;
	}
	//TAxis *axis = gr1->GetXaxis();
	//axis->SetLimits(0.,5.);                 // along X
	gr->GetHistogram()->SetMaximum(80);   // along          
	gr->GetHistogram()->SetMinimum(-5);  //   Y
	gr -> SetTitle(Form("Volt-Ampere characteristic (Neon tube);U_{y}, V;I_{a}, #muA"));
	gr -> SetMarkerColor(1);
	gr -> SetMarkerStyle(1);
	gr -> Draw("ALP");
}
