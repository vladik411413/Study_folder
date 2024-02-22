void plot_phys(){
	TCanvas *c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(8);
	TGraphErrors *gr = new TGraphErrors();
	fstream file;
	file.open("1.txt",ios::in);
	double N,theta,x,y,dx,dy,numerator,denominator;
	dx = 0.5;
	int n = 0;
	numerator = 0;
	denominator = 0;
	while(1){
		file >> theta >> N;
		n = gr -> GetN();
		y = N*pow(sin((6.28/360)*theta/2),4);
		dy = y*(1/sqrt(N)+(8/N));
		denominator+= 1/pow(dy,2);
		numerator+= y/pow(dy,2);
		cout << y << " " << dy << "\n";
		gr -> SetPoint(n,theta,y);
		gr -> SetPointError(n,dx,dy);
		if (file.eof()) break;
	}
	cout << numerator/denominator << " " << 1/sqrt(denominator);
	//TAxis *axis = gr1->GetXaxis();
	//axis->SetLimits(0.,5.);                 // along X
	//gr->GetHistogram()->SetMaximum(80);   // along          
	//gr->GetHistogram()->SetMinimum(-5);  //   Y
	gr -> SetTitle(Form("Checking the Rutherford formula;#theta, #circ;Nsin^{4}(#frac{#theta}{2})"));
	gr -> SetMarkerColor(1);
	gr -> SetMarkerStyle(20);
	gr -> Draw("ALP");
}
