void plot_phys(){
	TCanvas *c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(8);
	TGraphErrors *gr = new TGraphErrors();
	TGraph *func = new TGraph();
	double dx,dy,a,b,xx,yy;
  a = 0;
  b = 10;
	int n = 100;
  int i = 0;
  dx = 0;
  dy = 0;
  double x[n+1];
  double y[n+1];
  double xpol[n+1];
  double ypol[n+1];  
/*
  for(i=0;i<=n;i++){
    x[i] = a+(i*(b-a)/n);
    y[i] = cos(exp(x[i]/3.0)/10.0);
  }
*/
  for(i=0;i<=n;i++){
    x[i] = cos(3.14*(2*i)/(2*(double)n));
    y[i] = cos(exp(x[i]/3.0)/10.0);
  }
  for(i=0;i<n;i++){
    double sum = 0;
    xpol[i] = (x[i]+x[i+1])/2;
    for(int j=0;j<=n;j++){
      double pr = 1;
      for(int k=0;k<=n;k++){
      if(j!=k) pr=pr*(xpol[i]-x[k])/(x[j]-x[k]);
      } 
      sum+=y[j]*pr;
    }
    ypol[i] = sum;
  }
  i = 0;
	while(1){
		//i = gr -> GetN();
		func -> SetPoint(i,x[i],y[i]);
		if(i<n){
    gr -> SetPoint(i,xpol[i],ypol[i]);
		gr -> SetPointError(i,dx,dy);
    }
    i++;
		if (i>=n+1) break;
	}
	//TAxis *axis = gr1->GetXaxis();
	//axis->SetLimits(0.,5.);                 // along X
	//gr->GetHistogram()->SetMaximum(80);   // along          
	//gr->GetHistogram()->SetMinimum(-5);  //   Y
  double max = 0;
  double t = 0;
  for(i=0;i<n;i++){
    double t = ypol[i] - cos(exp(xpol[i]/3.0)/10.0);
    if(t<0) t = -t;
    if(i==0) max = t;
    if(t>max) max = t;
  }
	cout << "max |yi-Li| = " << max << "\n";	

	gr -> SetMarkerColor(1);
	gr -> SetMarkerStyle(20);
	TMultiGraph *mg = new TMultiGraph();
	mg -> SetTitle(Form("Curve LR1"));
	func->SetLineColor(kBlue);
	func -> SetMarkerStyle(8);
  func -> SetMarkerColor(4);
	mg->Add(gr,"APL");
	mg->Add(func,"PL");
	mg->Draw("ap");
	//TLegend *leg = new TLegend(0.1, 0.7, 0.3, 0.9);
	//leg->SetHeader("Curve");
	//leg->AddEntry(func,"#scale[0.6]{y = cos(#frac{e^{x/3}}{10})}","PL");
	//leg->Draw();
	c1->Update();
}
