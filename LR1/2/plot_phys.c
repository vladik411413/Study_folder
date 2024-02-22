void plot_phys(){
	TCanvas *c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);
	TGraphErrors *gr = new TGraphErrors();
	fstream file;
	file.open("400.txt",ios::in);
	double x,y,dx,dy;
	dx = 1;
	dy = 0.1;
	int n = 0;
	while(1){
		file >> x >> y;
		n = gr -> GetN();
		y = y+2;
		y = y/10;
		gr -> SetPoint(n,x,y);
		gr -> SetPointError(n,dx,dy);
		
		if (file.eof()) break;
	}
	gr -> SetTitle(Form("Volt-Ampere characteristic #lambda_{pt} = 400 nm; U, mV; I, nA"));
	gr -> SetMarkerColor(1);
	gr -> SetMarkerStyle(1);
	gr -> Draw("ALP");
}
