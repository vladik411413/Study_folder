void plot_phys(){
	TCanvas *c1 = new TCanvas("c1","plot 1",200,10,700,500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(8);
	TGraphErrors *gr = new TGraphErrors();
	TCanvas *c2 = new TCanvas("c2","plot 2",200,10,700,500);
	c2->SetGrid();
	c2->GetFrame()->SetBorderSize(8);
	TGraphErrors *gr2 = new TGraphErrors();
	fstream file;
	file.open("1.txt",ios::in);
	double dx,dy,R0,B,Tk,Rk,U0,Uln,I,P,R,T,alpha,Pch;
	double dI,dU0,dUln,dR,dT,dP,dalpha,dPch,dlnP,dlnT,dRk;
	dx = 0;
	dy = 0;
	int n = 0;
	R0 = 2;//Ohm
	B = 50;//K
	Tk = 294; //K (21 C)
	Rk = 2.92; //Ohm
	dRk = 0.02;
	while(1){
		file >> U0 >> Uln;
		n = gr -> GetN();
		n = gr2 -> GetN();
		dU0 = 0.005*U0+2;
		dUln = 0.005*Uln+0.002;
		dU0 = dU0/1000;
		U0 = U0/1000; //U0 (V)
		//U0 (V) Uln (V)
		
		
		I = U0/R0; //A
		dI = dU0/R0;
		P = Uln*I;
		dP = sqrt(pow(I*dUln,2) + pow(dI*Uln,2));
		R = R0*Uln/U0;
		dR = sqrt(pow(dUln/Uln,2) + pow(dU0/U0,2))*R;
		T = B + R*(Tk - B)/Rk;
		dT = sqrt(pow(dR/R,2) + pow(dRk/Rk,2))*T;
		Pch = 3.14*1.4e-6*5.670e-8*pow(T,4);
		dPch = Pch*4*dT/T;
		alpha = P/Pch;
		dalpha = sqrt(pow(dP/P,2) + pow(dPch/Pch,2))*alpha;
		dlnP = dP/P;
		dlnT = dT/T;
		
		gr -> SetPoint(n,log(T),log(P));
		gr -> SetPointError(n,dlnT,dlnP);
		gr2 -> SetPoint(n,log(T),log(alpha));
		gr2 -> SetPointError(n,dT/T,dalpha/alpha);
		//cout <<" dI = "<< dI << " dP = " << dP << " dR = " << dR << " dT = " << dT << " dln(P) = " << dlnP <<" dln(T) = "<< dlnT <<" dPch = "<< dPch <<" dalpha = "<< dalpha <<"\n";
		cout <<" "<< dI << " " << dP << " " << dR << " " << dT 
		<< " " << dlnP <<" "<< dlnT <<
		" "<< dPch <<" "<< dalpha <<"\n";
		if (file.eof()) break;
	}
	//TAxis *axis = gr1->GetXaxis();
	//axis->SetLimits(0.,5.);                 // along X
	//gr->GetHistogram()->SetMaximum(80);   // along          
	//gr->GetHistogram()->SetMinimum(-5);  //   Y
	c1->cd();
	gr -> SetTitle(Form("Dependence of power P versus temperature T;ln(T);ln(P)"));
	gr -> SetMarkerColor(1);
	gr -> SetMarkerStyle(1);//1
	gr -> Draw("AP");
	c2->cd();
	gr2 -> SetTitle(Form("Dependence of alpha versus temperature T;ln(T), K;ln(#alpha)"));
	gr2 -> SetMarkerColor(1);
	gr2 -> SetMarkerStyle(1);//1
	gr2 -> Draw("AP");
}
