
int n;
double poryadok = 4; //четвертый порядок точности eval


double newton_difference(int n1,int n2,double* x0, double* y0);
double y2p_evalue(double* x0,double* y0,int n1,int poryadok,double x);
double maxim(double* y1,double* y2,int n);
double fact(int k);

void plot_phys(){
	TCanvas *c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(8);
	TGraph *black = new TGraph();
	TGraph *blue = new TGraph();
  TGraph *red = new TGraph();
	double dx,dy,a,b;
  double xpol[n];
  double ypol[n];  
  double yp_left_0[n];
  double yp_cent_0[n];
  double blue_mas[n];
  double black_mas[n];
  double red_mas[n];
  double Real,CalcBlue,CalcRed,t1,m1,t2,m2,t3,m3,CalcBlack;
  int i,k,black_order,blue_order,red_order;
  blue_order = 1;
  red_order = 2;
  black_order = 4;
  char buf[30];
  a =-0.8;
  b =0.8;
  for(n = 50;n < 200;n++){
    double *x = new double[n];
    double *y = new double[n];
    for(i=0;i<n;i++){
      x[i] = a+((i+1)*(b-a)/n);
      y[i] = exp(-x[i])*sin(x[i]);
    }

    for(i=0;i<n-9;i++){
      Real = -2*exp(-x[i])*cos(x[i]); //Real 2 pr
      CalcBlue = y2p_evalue(x,y,i,blue_order,x[i]);
      CalcRed = y2p_evalue(x,y,i,red_order,x[i]);
      CalcBlack = y2p_evalue(x,y,i,black_order,x[i]);

      t1 = Real-CalcBlue;
      if(t1<0) t1 = -t1;
      if(i==0) m1 = t1;
      if(t1>m1) m1 = t1;
      
      t2 = Real-CalcRed;
      if(t2<0) t2 = -t2;
      if(i==0) m2 = t2;
      if(t2>m2) m2 = t2;

      t3 = Real-CalcBlack;
      if(t3<0) t3 = -t3;
      if(i==0) m3 = t3;
      if(t3>m3) m3 = t3;
    }
    delete [] x;
    delete [] y;
    k = blue -> GetN();
    blue -> SetPoint(k,log10(n),log10(m1));
    red -> SetPoint(k,log10(n),log10(m2)); 
    black -> SetPoint(k,log10(n),log10(m3)); 
  }


	//TAxis *axis = gr1->GetXaxis();
	//axis->SetLimits(0.,5.);                 // along X
	//gr->GetHistogram()->SemMaximum(80);   // along          
	//gr->Geram()->SetMinimumMinimum(-5);  //   Y
  

	black -> SetMarkerColor(1);
	black -> SetMarkerStyle(1);
	TMultiGraph *mg = new TMultiGraph();
	mg -> SetTitle(Form("Accuracy dependence from number of points, n;log_{10}(n);log_{10}(err)"));
	blue->SetLineColor(kBlue);
	blue -> SetMarkerStyle(1);
  blue -> SetMarkerColor(4);
	red -> SetMarkerColor(2);
	red -> SetMarkerStyle(1);
  red->SetLineColor(kRed);
  

	mg->Add(blue,"APL");
  mg->Add(red,"PL");
  mg->Add(black,"PL");
	mg->Draw("ap");
  TLegend *leg = new TLegend(0.1, 0.1, 0.3, 0.3);
  snprintf(buf,sizeof(buf),"%d order accuracy",blue_order);
	leg->AddEntry(blue,buf,"PL");
  snprintf(buf,sizeof(buf),"%d order accuracy",red_order);
  leg->AddEntry(red,buf,"PL");
  snprintf(buf,sizeof(buf),"%d order accuracy",black_order);
  leg->AddEntry(black,buf,"PL");
	leg->Draw();
	//TLegend *leg = new TLegend(0.1, 0.7, 0.3, 0.9);
	//leg->SetHeader("Curve");
	//leg->A(func,"#scale[0.6ale[0.6]{y = cos(#frac{e^{x/3}}{10})}","PL");
	//leg->Draw();
	c1->Update();
}

double newton_difference(int n1,int n2,double* x0, double* y0){
int i;
double t;
double *x = new double[n2-n1+1];
double *y = new double[n2-n1+1];
for(i=0;i<n2-n1+1;i++) y[i] = y0[n1+i];
for(i=0;i<n2-n1+1;i++) x[i] = x0[n1+i];
double *yp = new double[n2-n1];
for(int j = 0;n2-n1-j>0;j++){
for(i=0;i<n2-n1-j;i++) {
  yp[i] = (y[i+1]-y[i])/((x[i+1+j]-x[i]));
}

for(i=0;i<n2-n1-j;i++) y[i] = yp[i];

}
t=yp[0];
delete [] x;
delete [] y;
delete [] yp;
return t;
}
double y2p_evalue(double* x0,double* y0,int n1,int poryadok,double x){
double sum_m,pr,sum_k,sum_j;
//double psi[n2-n1+1];
int i,k,m,j,Flag;
//for(i=0;i<n2-n1+1;i++) psi[i] = x-x0[n1+i];
//sum_k = newton_difference(n1,n2,x0,y0)*fact(n2-n1);
sum_k=0;
for(k=2;k<poryadok+3;k++){
  sum_m = 0;
  for(m = 0;m < k;m++){
    sum_j = 0;
    for(j = 0;j < k;j++){
      if(m!=j){
        pr = 1;
        for(i = 0;i < k;i++){
          if((i-j)*(i-m)!=0){
            pr*=x-x0[n1+i];

          }
        }
       sum_j+=pr;
      }
    }
  sum_m+= sum_j;
  }
  //cout << "sum_m " << sum_m << " k "<< k <<" poryadok "<<poryadok<<"\n";	
  sum_k+= sum_m * newton_difference(n1,n1+k,x0,y0);
}


return sum_k;
}
double maxim(double* y1,double* y2,int n){
  double m = 0;
  double t = 0;
  for(int i=0;i<n;i++){
    t = y2[i] - y1[i];
    if(t<0) t = -t;
    if(i==0) m = t;
    if(t>m) m = t;
  }
	cout << "max |y2-y1| = " << m << "\n";	
  return m;
}
double fact(int k){
  int pr = 1;
  for(int i = 2;i<=k;i++){
    pr=pr*i;
  }
  return (double)pr;
}
