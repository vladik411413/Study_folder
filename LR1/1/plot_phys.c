void plot_phys(){
	TCanvas *c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);
	TGraphErrors *gr_1 = new TGraphErrors();
	TGraphErrors *gr_2 = new TGraphErrors();
	
	TGraphErrors *gr_3 = new TGraphErrors();
	TGraphErrors *gr_4 = new TGraphErrors();
	fstream file;
	file.open("1.txt",ios::in);
	double x,y_1,y_2,y_3,y_4,dx,dy;
	dx = 0.05;
	dy = 0.33;
	int n = 0;
	while(1){
		file >> x >> y_1 >> y_2 >> y_3 >> y_4 ;
		n = gr_1 -> GetN();
		gr_2 -> GetN();
		gr_3 -> GetN();
		gr_4 -> GetN();
		gr_1 -> SetPoint(n,x,y_1);
		gr_2 -> SetPoint(n,x,y_2);
		gr_3 -> SetPoint(n,x,y_3);
		gr_4 -> SetPoint(n,x,y_4);
		gr_1 -> SetPointError(n,dx,dy);
		gr_2 -> SetPointError(n,dx,dy);
		gr_3 -> SetPointError(n,dx,dy);
		gr_4 -> SetPointError(n,dx,dy);
		
		if (file.eof()) break;
	}
		gr_1 -> SetMarkerColor(1);
		gr_2 -> SetMarkerColor(2);
		gr_3 -> SetMarkerColor(3);
		gr_4 -> SetMarkerColor(4);
		gr_1 -> SetMarkerStyle(7);
		gr_2 -> SetMarkerStyle(7);
		gr_3 -> SetMarkerStyle(7);
		gr_4 -> SetMarkerStyle(7);




	TMultiGraph *mg = new TMultiGraph();
	mg -> SetTitle(Form("Volt-Ampere characteristic of a photoelectric element; U, V; I, nA"));
	mg->Add(gr_1);
	mg->Add(gr_2);
	mg->Add(gr_3);
	mg->Add(gr_4);
	mg->Draw("ALP");
}
