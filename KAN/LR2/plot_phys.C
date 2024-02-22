int s = 60;
int n = 2*s+1;
double poryadok = 4; //четвертый порядок точности eval


double newton_difference(int n1,int n2,double* x0, double* y0);
double evalue(double* x0,double* y0,int n1,int n2,int poryadok,double x);
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
  a = -0.8;
  b = 0.8;
  double x[n];
  double y[n];
  double xpol[n];
  double ypol[n];  
  double yp_left_0[n];
  double yp_cent_0[n];
  double blue_mas[n];
  double black_mas[n];
  double red_mas[n];
  int i;

  for(i=0;i<n;i++){
    x[i] = a+((i+1)*(b-a)/n);
    y[i] = exp(-x[i])*sin(x[i]);
  }

  for(i=0;i<n-6;i++){
    yp_left_0[i] = exp(-x[i])*(cos(x[i])-sin(x[i]));
    blue_mas[i] = -2*exp(-x[i])*cos(x[i]); //Real 2 pr
    black_mas[i] = evalue(x,y,i,i+2,4,x[i]);
    red_mas[i] = 2*newton_difference(i,i+2,x,y);
  }

  double tempx,tempy;
	for(i=0;i<n-6;i++){
  blue -> SetPoint(i,x[i],blue_mas[i]);
  black -> SetPoint(i,x[i],black_mas[i]);
  red -> SetPoint(i,x[i],red_mas[i]); 
  } 
	//TAxis *axis = gr1->GetXaxis();
	//axis->SetLimits(0.,5.);                 // along X
	//gr->GetHistogram()->SemMaximum(80);   // along          
	//gr->Geram()->SetMinimumMinimum(-5);  //   Y
  

	black -> SetMarkerColor(1);
	black -> SetMarkerStyle(1);
	TMultiGraph *mg = new TMultiGraph();
	mg -> SetTitle(Form("Curve LR1"));
	blue->SetLineColor(kBlue);
	blue -> SetMarkerStyle(1);
  blue -> SetMarkerColor(4);
	red -> SetMarkerColor(2);
	red -> SetMarkerStyle(1);
  red->SetLineColor(kRed);
	mg->Add(blue,"APL");
	mg->Add(black,"PL");
  mg->Add(red,"PL");
	mg->Draw("ap");
	//TLegend *leg = new TLegend(0.1, 0.7, 0.3, 0.9);
	//leg->SetHeader("Curve");
	//leg->A(func,"#scale[0.6ale[0.6]{y = cos(#frac{e^{x/3}}{10})}","PL");
	//leg->Draw();
	c1->Update();
}

double newton_difference(int n1,int n2,double* x0, double* y0){
int i;
double y[n2-n1+1];
double x[n2-n1+1];
for(i=0;i<n2-n1+1;i++) y[i] = y0[n1+i];
for(i=0;i<n2-n1+1;i++) x[i] = x0[n1+i];
double yp[n2-n1];
for(int j = 0;n2-n1-j>0;j++){
for(i=0;i<n2-n1-j;i++) {
  yp[i] = (y[i+1]-y[i])/((x[i+1+j]-x[i]));
}

for(i=0;i<n2-n1-j;i++) y[i] = yp[i];

}
return yp[0];
}
double evalue(double* x0,double* y0,int n1,int n2,int poryadok,double x){
double sum_m,pr,sum_k,sum_j;
double psi[n2-n1+1];
int i,k,m,j,Flag;
sum_k = newton_difference(n1,n2,x0,y0);
for(i=0;i<n2-n1+1;i++) psi[i] = x0[n1+i]-x;
sum_k = newton_difference(n1,n2,x0,y0)*fact(n2-n1);
for(k=1;k<poryadok;k++){
  sum_m = 0;
  for(m = 0;m < k;m++){
    sum_j = 0;
    for(j = 0;j < k;j++){
      pr = 1;
      Flag = 0;
      for(i = 0;i < k;i++){
        if((i-j)*(i-m)!=0){
          Flag=1;
          pr*=psi[i];
        }
      }
      if(Flag) sum_j+=pr;
    }
  sum_m+= sum_j;
  }
  sum_k+= sum_m * newton_difference(n1,n2+k,x0,y0);
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
