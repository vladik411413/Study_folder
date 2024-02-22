void plot_phys(){
	TCanvas *c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);
	c1->DrawFrame(0,-900,6,900,"Dependence of the cut off potential U from frequency #omega; #omega, x10^{15} c^{-1}; U, mV"); //zoom
	TGraphErrors *gr = new TGraphErrors();
	fstream file;
	file.open("data.txt",ios::in);
	double x,y,lambda,dx,dy;
	int n = 0;
	dx = 0;
	while(1){
		file >> lambda >> y >> dy;
		n = gr -> GetN();
		x = 2*3.14*300/lambda;
		gr -> SetPoint(n,x,y);
		gr -> SetPointError(n,dx,dy);
		if (file.eof()) break;
	}
	gr -> SetMarkerColor(1);
	gr -> SetMarkerStyle(20);
	gr -> Draw("P");
}
