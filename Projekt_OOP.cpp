#include "functions_TTT.h"

using namespace std;

int main()
{
	Program_Controller p_con;
    while (p_con.running)
    {
    	p_con.p_fbuffer.Push_WorkBuffer("Testing");
    	p_con.p_fbuffer.Push_WorkBuffer("Trying");
    	p_con.p_fbuffer.Push_WorkBuffer("Figuring");
    	p_con.p_fbuffer.Push_WorkBuffer("Bothering");
    	// update the display time, prior to this all of the logic and work buffer updating happens.
    	p_con.p_fbuffer.Update_OutputBuffer();
    	p_con.p_fbuffer.Clear_WorkBuffer();
        p_con.p_timer.Tick();
        cout << p_con.p_fbuffer.Return_OutputBuffer();
        //cout << "Time: " << (p_con.p_timer.work_time + p_con.p_timer.sleep_time).count() << "\n";
        
    }
}
