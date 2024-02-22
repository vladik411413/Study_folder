void plot_phys(){
	TCanvas *c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);
	TGraphErrors *gr = new TGraphErrors();
	fstream file;
	file.open("K.txt",ios::in);
	double x,k,y,dx,dy,y_k,dk;
	dx = 0.1;
	dk = 0.033;
	int n = 0;
	while(1){
		file >> x >> k >> y >> dy;
		n = gr -> GetN();
		y_k = y/k;
		dy = sqrt(pow(dk*y/(k*k),2)+pow(dy/k,2));
		gr -> SetPoint(n,x,y_k);
		gr -> SetPointError(n,dx,dy);
		std::cout << "k = "<< k << " I_kk = " << y_k << " d_I_kk = " << dy << std::endl;
		if (file.eof()) break;
	}
	gr -> SetTitle(Form("Spectrum characteristic;#lambda, nm;I_{ k}, nA"));
	gr -> SetMarkerColor(1);
	gr -> SetMarkerStyle(20);
	gr -> Draw("ALP");
}
