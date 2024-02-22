void plot_phys(){
	TCanvas *c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);
	TGraphErrors *gr_1 = new TGraphErrors();
	TGraphErrors *gr_2 = new TGraphErrors();
	TGraphErrors *gr_3 = new TGraphErrors();
	fstream file;
	file.open("1.txt",ios::in);
	double x,y,dx,dy;
	dx = 0;
	int n = 0;
	int theta;
	while(1){
		file >> theta >> x >> y;
		dy = sqrt(y);
		if (theta == 9){
			n = gr_1 -> GetN();
			gr_1 -> SetPoint(n,x,y);
			gr_1 -> SetPointError(n,dx,dy);
		}
		if (theta == 10){
			n = gr_2 -> GetN();
			gr_2 -> SetPoint(n,x,y);
			gr_2 -> SetPointError(n,dx,dy);
		}
		if (theta == 11){
			n = gr_3 -> GetN();
			gr_3 -> SetPoint(n,x,y);
			gr_3 -> SetPointError(n,dx,dy);
		}
		
		if (file.eof()) break;
	}
		gr_1 -> SetMarkerStyle(20);
		gr_2 -> SetMarkerStyle(21);
		gr_3 -> SetMarkerStyle(22);
		gr_1 -> SetMarkerSize(1);
		gr_2 -> SetMarkerSize(1);
		gr_3 -> SetMarkerSize(1);



	TMultiGraph *mg = new TMultiGraph();
	mg -> SetTitle(Form("Dependence of intensity of x-ray component on accelerating voltage; U, kV; R"));
	mg->Add(gr_1);
	mg->Add(gr_2);
	mg->Add(gr_3);
	mg->Draw("ALP");
	
	TLegend *leg = new TLegend(0.1, 0.7, 0.3, 0.9);
	leg->SetHeader("The Legend Title");
	leg->AddEntry(gr_1,"#theta = 9#circ","p");
	leg->AddEntry(gr_2,"#theta = 10#circ","p");
	leg->AddEntry(gr_3,"#theta = 11#circ","p");
	leg->Draw();

}
