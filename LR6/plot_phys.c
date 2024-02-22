void plot_phys(){
	TCanvas *c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(8);
	TGraphErrors *gr = new TGraphErrors();
	TGraph *func = new TGraph();
	fstream file;
	file.open("6.txt",ios::in);
	double x,y,p,dpd,dU,d,U,pd,B,A,Umin,xmin;
	Umin = 400;
	xmin = 0.4;
	p = 600; //Па
	dU = 20;
	B = 487;
	A = 20;
	int n = 0;
	cout <<"pd, Па*м"<<"   U,В\n";
	while(1){
		n = gr -> GetN();
		file >> d >> U;
		d = d/100000;
		pd = p*d;
		dpd = 1e2*d + (p*1/1e5);
		cout << pd << "   " << U << "\n";
		y = (Umin/xmin)*pd/log(pd*2.71/xmin);
		func -> SetPoint(n,pd,y);
		gr -> SetPoint(n,pd,U);
		gr -> SetPointError(n,dpd,dU);
		if (file.eof()) break;
	}
	//TAxis *axis = gr1->GetXaxis();
	//axis->SetLimits(0.,5.);                 // along X
	//gr->GetHistogram()->SetMaximum(80);   // along          
	//gr->GetHistogram()->SetMinimum(-5);  //   Y
	
	gr -> SetMarkerColor(1);
	gr -> SetMarkerStyle(20);
	TMultiGraph *mg = new TMultiGraph();
	mg -> SetTitle(Form("Dependence of breakdown voltage on p*d at p = 600 Pa;p*d, Pa*m;U,V"));
	func->SetLineColor(kBlue);
	mg->Add(gr,"AP");
	mg->Add(func,"PL");
	mg->Draw("ap");
	TLegend *leg = new TLegend(0.1, 0.7, 0.3, 0.9);
	leg->SetHeader("Paschen curve");
	leg->AddEntry(func,"#scale[0.6]{U = #frac{B*pd}{ln(#frac{A*pd}{ln(1+1/#gamma)})}}","PL");
	leg->Draw();
	c1->Update();
}
