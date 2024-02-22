void plot_phys(){
	TCanvas *c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);
	TGraphErrors *gr = new TGraphErrors();
	fstream file;
	file.open("data.txt",ios::in);
	double x,y,dx,dy;
	int n = 0;
	dy = 1;
	dx = 0.05;
	while(1){
		file >> x >> y;
		n = gr -> GetN();
		
		gr -> SetPoint(n,x,y);
		gr -> SetPointError(n,dx,dy);
		
		if (file.eof()) break;
	}
	gr -> SetTitle(Form("Light characteristic;H, mm;#iota, nA"));
	gr -> SetMarkerColor(1);
	gr -> SetMarkerStyle(20);
	gr -> Draw("AP");
}
