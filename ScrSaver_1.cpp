


//  ���� ���� �������� Lego-�������. �� ��������� �������� ��������.
//  � ������ ���������� ������� ������ ��������� �� �������� Lego-�������. 
//  ��� ������ ����� ����������� � ������ Windows-�������.




#include         <windows.h> 
#include          <stdlib.h>


LRESULT CALLBACK Timer_101(HWND  hWnd, UINT message, UINT_PTR idEvent, DWORD dwTime);

namespace
{
	
	
    HDC             hdc_l;
}



namespace Lego   //-------------------------- namespace Lego --------------------
{ 
	
            int           Screen_S = 0; 
            
     	    HPEN       hScreenS_Pen[2];       //   0 - ���� ����, 1 - ���� �������� (��������)  
	
	extern  int              Timer_CLK, 
	                         MouseMove,       //   DemoBusy, 
	                         StatusBar,
	                           ToolBar;                    	                          
                                              //	extern  HWND                hWndSB,
	extern  HWND                  hWnd;       //	Zastavka      Zast(40, 41, 40, 41);   

    extern  RECT             rc_Global;
 
 
 
 
                 
	//--------------------------------------------------------------------------------------------------------------
	//          ����� �������� ��������
	//--------------------------------------------------------------------------------------------------------------
	class Zastavka
	{
		public: 
		/////////////////////////////////////	
		unsigned __int16 x1, x2, y1, y2,   //   ���������� �������
		                              k,   //   ���-�� ��������� � ����� ��������										                      
					     anKoord[5][42];   //   ������ ���������� ��������   
	
	    
	    int               old_MouseMove;	                      			
		
		            ////////////////////
		                     Zastavka();
		                    ~Zastavka();   
			
		void                     Line();
		void                     Blow();
	    void            Close_Zast(int);
			
	} Zast;





	///////////////////////////////////////////////////////////////                                 ��������� ��������
	void StartScreenSaver_1()                                    //
	{
		
		 if(Screen_S == 0)
		 {
				
			srand(Timer_CLK);

	        Zast.x1 = rand()%rc_Global. right; 
	        Zast.x2 = rand()%rc_Global. right; 	
	        Zast.y1 = rand()%rc_Global.bottom; 
	        Zast.y2 = rand()%rc_Global.bottom; 			
				
            Screen_S = 1;                                                                      //   �������� ��������
  		    SetTimer(hWnd, 101, 50, (TIMERPROC)Timer_101);                     // ��������� �������� ������� Timer_101 				
		 }  		 
	}










	

	


//---------------------------------------------------------------------------------------------------------------------
//          ������ ������ �������� ��������
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------


    ///////////////////////////////////////////////////////////////
    Zastavka::Zastavka()                                         //
	{	   	
	   x1 = 40; // a1;
	   x2 = 41; // a2; 	
	   y1 = 40; // b1;
	   y2 = 41; // b2;	
	   
	   k  = 41;                                                   //  ���-�� ��������� (��������) � �������� ��������
	   
	   hScreenS_Pen[0] = CreatePen(0, 1, 0); 
	   hScreenS_Pen[1] = CreatePen(0, 1, RGB(66, 170,255));   
	}



    ///////////////////////////////////////////////////////////////
    Zastavka::~Zastavka()                                        //
	{	
		
	//	DeleteObject(hScreenS_Pen[0]); 
	//	DeleteObject(hScreenS_Pen[1]); 		
	}



    ///////////////////////////////////////////////////////////////
	void Zastavka::Close_Zast(int u)                             //
	{	
		hdc_l = GetDC(hWnd);                                                            //  �������� �������� ������
		
		SelectObject(hdc_l, hScreenS_Pen[0]);							   // ������ (�����) ����� ������ �������...
		MoveToEx(hdc_l, anKoord[1][u], anKoord[2][u], 0); 			
		LineTo  (hdc_l, anKoord[3][u], anKoord[4][u]   );	
								    												
		if(u == 0) InvalidateRect(hWnd, &rc_Global, 1);	
	
		ReleaseDC(hWnd, hdc_l);	
	}



    ///////////////////////////////////////////////////////////////
	void Zastavka::Line()                                        //
	{		
	    Blow();
		
		hdc_l = GetDC(hWnd);                                                              //  �������� �������� ������
	
		SelectObject(hdc_l, hScreenS_Pen[0]);								   // ������ (�����) ����� ������ �������...
		MoveToEx(hdc_l, anKoord[1][k], anKoord[2][k], 0); 			
		LineTo  (hdc_l, anKoord[3][k], anKoord[4][k]   );	         
        
        SelectObject(hdc_l, hScreenS_Pen[1]);                                               //  ������ ����� �������

		MoveToEx(hdc_l, x1, y1,  0 ); 			
		LineTo  (hdc_l, x2, y2);	
		
		ReleaseDC(hWnd, hdc_l);												            //  ��������� �������� ������
		
		for(int i = k; i > 0; i--)                          //  ���������� � ������� ���������� ������������ ��������
		{
			anKoord[1][i] = anKoord[1][i-1];
			anKoord[2][i] = anKoord[2][i-1];
			anKoord[3][i] = anKoord[3][i-1];
			anKoord[4][i] = anKoord[4][i-1];		
		}
		
		anKoord[1][0] = x1;
		anKoord[2][0] = y1;
		anKoord[3][0] = x2;
		anKoord[4][0] = y2;		
	}


    ///////////////////////////////////////////////////////////////
	void Zastavka::Blow()                                        //
	{
		static int napr_X1 = 1,
		           napr_X2 = 1,
		           napr_Y1 = 1,
		           napr_Y2 = 1;
		
		x1 += 2 * napr_X1;	
		x2 += 1 * napr_X2;		    
		y1 += 3 * napr_Y1;
		y2 += 4 * napr_Y2;			
		
		
		if(y1 > rc_Global.bottom-3-StatusBar) napr_Y1 = -1;		                                  //  -50  rc.bottom  rc.right
		if(y2 > rc_Global.bottom-3-StatusBar) napr_Y2 = -1;
		
		if(y1 <  5+ToolBar) napr_Y1 =  1;			
		if(y2 <  5+ToolBar) napr_Y2 =  1;
		
		if(x1 > rc_Global.right-3) napr_X1 = -1;
		if(x2 > rc_Global.right-3) napr_X2 = -1;		
						
		if(x1 <          2) napr_X1 =  1;
		if(x2 <          2) napr_X2 =  1;				
	}
	

}  //============================ namespace Lego ==================================





using namespace  Lego;  




LRESULT CALLBACK Timer_101(HWND hWnd, UINT message, UINT_PTR idEvent, DWORD dwTime)  // ������� ��������� ��������� ��...  
{																						//                  ...�������
		
		if(!IsIconic(hWnd))		                      //  ���� ���� �� ��������������, �� ��������� �������� ��������      						   
		{ 				
			if(Screen_S > 0) Zast.Line();		                                                //  ������ ����� �����				   							
							   
			if(Screen_S < 0) Zast.Close_Zast(-Screen_S);							       //  ������� ��������� �����  			
			
			Screen_S ++;	
			
			///////////////////////////////////////////////////
			if(Screen_S == 20) Zast.old_MouseMove = MouseMove;	
			if(Screen_S  > 20)
			{
			   if(Zast.old_MouseMove < MouseMove)
			   {
					
		          Screen_S = -Zast.k;
		          Zast.Close_Zast(-Screen_S);
		          Screen_S ++;																				
			   }
			}
			////////////////////////////////////////////////////

			
			if(Screen_S == 0)
		    {		   	
		   	   Zast.Close_Zast(0);	                                                        // ������� ��������� �����	   	
		   	   KillTimer(hWnd, 101);	                         // ���������� Timer_2 (���� �������� - ���� ���������)
		    }
							
		}   
		else Screen_S = 1;

return 0;
}


			
	
		
		
		
		
		
		
		
		
		
		

