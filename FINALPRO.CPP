//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************


#include<bits/stdc++.h>

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************
using namespace std;
class product
{
 int pno;
 char name[50];
 float price,qty,tax,dis;
 public:
	void create_product()
	{
	 cout<<"\nPlease Enter The Product No. of The Product ";
	 cin>>pno;
	 cout<<"\n Enter Burger's Name's Length";
	 int n;
	 cin>>n;
	 cout<<"\n\nPlease Enter The Name of The burger ";
	 for(int i=0;i<n;i++)
     {

         cin>>name[i];
     }
	 cout<<"\nPlease Enter The Price of The burger ";
	 cin>>price;
	 cout<<"\nPlease Enter The Discount (%) ";
	 cin>>dis;
	 }

	void show_product()
	{
	 cout<<"\nThe Product No. of The burger : "<<pno;
	 cout<<"\nThe Name of The burger : ";
	 puts(name);
	 cout<<"\nThe Price of The burger : "<<price;
	 cout<<"\nDiscount : "<<dis;
	 }

  int  retpno()
  {return pno;}

  float retprice()
  {return price;}

  char* retname()
  {return name;}

  int retdis()
  {return dis;}

};         //class ends here



//***************************************************************
//    	global declaration for stream object, object
//****************************************************************

 fstream fp;
 product pr;


//***************************************************************
//    	function to write in file
//****************************************************************

void write_product()
   {
    fp.open("Shop.dat",ios::out|ios::app);
    pr.create_product();
    fp.write((char*)&pr,sizeof(pr));
    fp.close();
    cout<<"\n\nThe Product Has Been Created ";

   }


//***************************************************************
//    	function to read all records from file
//****************************************************************


void display_all()
{

    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("Shop.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(pr)))
	{
	 pr.show_product();
	 cout<<"\n\n====================================\n";

	 }
    fp.close();

}


//***************************************************************
//    	function to read specific record from file
//****************************************************************


void display_sp(int n)
{
    int flag=0;
    fp.open("Shop.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(pr)))
	{
	 if(pr.retpno()==n)
		{

		 pr.show_product();
		 flag=1;
		}
	}
    fp.close();
if(flag==0)
 cout<<"\n\nrecord not exist";

}


//***************************************************************
//    	function to modify record of file
//****************************************************************


void modify_product()
{
    int no,found=0;

    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The Product No. of The Product";
    cin>>no;
    fp.open("Shop.dat",ios::in|ios::out);
    while(!fp.eof() && found==0)
	   {
	    if(pr.retpno()==no)
		   {
		    pr.show_product();
		    cout<<"\nPlease Enter The new Details of Product"<<endl;
		    pr.create_product();
		    int pos=fp.tellg();
		    fp.seekp(pos);
		    fp.write((char*)&pr,sizeof(pr));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		   }
	     }
    fp.close();
    if(found==0)
    cout<<"\n\n Record Not Found ";

}


//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_product()
   {
    int no;
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete";
    cin>>no;
    fp.open("Shop.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);

    while(fp.read((char*)&pr,sizeof(pr)))
	{
	 if(pr.retpno()!=no)
		{
		 fp2.write((char*)&pr,sizeof(product));
		 }
	 }
    fp2.close();
    fp.close();
    remove("Shop.dat");
    rename("Temp.dat","Shop.dat");
    cout<<"\n\n\tRecord Deleted ..";

    }


//***************************************************************
//    	function to display all products price list
//****************************************************************

    void menu()
    {

     fp.open("Shop.dat",ios::in);
     if(!fp)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
       cout<<"\n\n\n Program is closing ....";

       exit(0);
     }

     cout<<"\n\n\t\tProduct MENU\n\n";
	  cout<<"============================================================\n";
	  cout<<"P.NO.\t\tNAME\t\tPRICE\t\tDISCOUNT\n";
	  cout<<"============================================================\n";

      while(fp.read((char*)&pr,sizeof(product)))
	 {
	   cout<<pr.retpno()<<"\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<"\t\t"<<pr.retdis()<<endl;
	}
     fp.close();
}




//***************************************************************
//    	function to place order and generating bill for Products
//****************************************************************


   void place_order()
   {
    int  order_arr[50],quan[50],c=0;
    float amt,damt,total=0;
    char ch='Y';
    menu();
    cout<<"\n============================";
    cout<<"\n    PLACE YOUR ORDER";
    cout<<"\n============================\n";
    do{
	 cout<<"\n\nEnter The Product No. Of The burger : ";
	 cin>>order_arr[c];
	 cout<<"\nQuantity in number : ";
	 cin>>quan[c];
	 c++;
	 cout<<"\nDo You Want To Order Another Product ? (y/n)";
	 cin>>ch;
    }while(ch=='y' ||ch=='Y');
    cout<<"\n\nThank You For Placing The Order";
      cout<<"\n\n\n*************************************INVOICE************************************";
      cout<<"\n________________________________________________________________________________";
      cout<<"\nPr No.\tPr Name\t\t     Quantity \tPrice \tAmount \tdiscount    net amount\n";
      cout<<"________________________________________________________________________________";
      for(int x=0;x<=c;x++)
	{
		 fp.open("Shop.dat",ios::in);
		 fp.read((char*)&pr,sizeof(product));
		  while(!fp.eof())
			{
			if(pr.retpno()==order_arr[x])
				{
				 amt=pr.retprice()*quan[x];
				 damt=amt-(amt*pr.retdis()/100);
				 cout<<"\n"<<order_arr[x]<<"\t\t\t"<<pr.retname()<<"\t\t"<<quan[x]<<"\t"<<pr.retprice()<<"\t"<<amt<<"\t "<<pr.retdis()<<"\t     "<<damt;
				 total+=damt;
				}
			fp.read((char*)&pr,sizeof(product));
			}

		 fp.close();
	 }
       cout<<"\n\n\n\n\n\t\t\t\tTOTAL = "<<total;

    }


//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{

 //cout<<"**********************************************************************************";
 //cout<<"******************************************************************************";
 cout<<"\n\n\n\t\t\t       FASTRACK BURGERS";
 cout<<"\n\t\t\t\t   PROJECT";
 cout<<"\n\n\n________________________________________________________________________________";
 cout<<"\n\nMADE BY : UTKARSH GUPTA AND JAI NAGPAL";
 cout<<"\n\nSCHOOL : BAL MANDIR SR SEC SCHOOL";
 cout<<"\n________________________________________________________________________________";
  cout<<"\n________________________________________________________________________________";
  cout<<"\n________________________________________________________________________________";
  cout<<"\n________________________________________________________________________________";
   cout<<"\n________________________________________________________________________________";


}




//***************************************************************
//    	ADMINSTRATOR MENU FUNCTION
//****************************************************************
void admin_menu()
{

  char ch2;
  //cout<<"******************************************************************************";
  cout<<"\n\n\t\t\t WELCOME TO FAST TRACK BURGERS!!";
// cout<<"\n\n******************************************************************************";
  cout<<"\n______________________________________________________________________________";
  cout<<"\n\t\t\t\tADMIN MENU";
  cout<<"\n\n\t\t\t1.CREATE PRODUCT";
  cout<<"\n\n\t\t\t2.DISPLAY ALL PRODUCTS";
  cout<<"\n\n\t\t\t3.SEARCH PRODUCT";
  cout<<"\n\n\t\t\t4.MODIFY PRODUCT";
  cout<<"\n\n\t\t\t5.DELETE PRODUCT";
  cout<<"\n\n\t\t\t6.VIEW PRODUCT MENU";
  cout<<"\n\n\t\t\t7.BACK TO MAIN MENU";
  cout<<"\n\n\t\t\tPlease Enter Your Choice (1-7) ";
  cin>>ch2;
  switch(ch2)
  {
    case '1':
	      write_product();
	      break;
    case '2': display_all();break;
    case '3':
	       int num;

	       cout<<"\n\n\tPlease Enter The Product No. ";
	       cin>>num;
	       display_sp(num);
	       break;
      case '4': modify_product();break;
      case '5': delete_product();break;
      case '6': menu();

      case '7': break;
      default:cout<<"\a";admin_menu();
   }
}


//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
  char ch;
  intro();
  do
    {

	  //cout<<"*******************************************************************************";
	  cout<<"\n\n\t\t\tWELCOME TO FASTTRACK BURGERS";
	 // cout<<"\n\n*******************************************************************************";
	  cout<<"\n\n_______________________________________________________________________________";
	  cout<<"\n\n\n\tMAIN MENU";
	  cout<<"\n\n\t01. CUSTOMER";
	  cout<<"\n\n\t02. ADMINISTRATOR";
	  cout<<"\n\n\t03. EXIT";
	  cout<<"\n\n\tPlease Select Your Option (1-3) ";
	  cin>>ch;
	  cout<<"_______________________________________________________________________________";
	  switch(ch)
	  {
		 case '1':
			   place_order();

			   break;
		  case '2': admin_menu();
			    break;
		  case '3':exit(0);
		  default :cout<<"\a";
	}
    }while(ch!='3');
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************
