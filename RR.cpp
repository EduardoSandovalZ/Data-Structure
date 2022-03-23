#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <climits>
using namespace std;
struct process_struct
{
    int pid;
    int at;
    int bt;
    int ct, wt, tat, rt, start_time;
} ps[100];

bool comparatorAT(struct process_struct a, struct process_struct b)
{
    int x = a.at;
    int y = b.at;
    return x < y;
    /*
    if (x>y){
        return false; //apliica la busqueda
    }else{
        return true; // no apliques la busqueda
    }
     */
}
bool comparatorPID(struct process_struct a, struct process_struct b)
{
    int x = a.pid;
    int y = b.pid;
    return x < y;
}

int main()
{
    int n, index;
    float bt_remaining[100], cpu_utilization;
    queue<int> q;
    bool visited[100] = {false}, is_first_process = true;
    int current_time = 0, max_completion_time;
    int completed = 0, tq, total_idle_time = 0, length_cycle;
    cout << "INGRESE EL NUMERO TOTAL DE PROCESOS: ";
    cin >> n;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    cout << fixed << setprecision(2);
    for (int i = 0; i < n; i++)
    {
        cout << "\nPROCESO " << i << endl;
        cout << "INGRESE EL TIEMPO DE LLEGADA DEL PROCESO: " << endl;
        cin >> ps[i].at;
        ps[i].pid = i;
        cout << "INGRESE LA DURACION DEL  PROCESO" << endl;
        cin >> ps[i].bt;
        bt_remaining[i] = ps[i].bt;
    }
    cout << "Ingrese el Quantum: ";
    cin >> tq;
    // estructura de busqueda basada en el tiempo de llegafa en orden de incremento
    sort(ps, ps + n, comparatorAT);
    q.push(0);
    visited[0] = true;
    while (completed != n)
    {
        index = q.front();
        q.pop();
        if (bt_remaining[index] == ps[index].bt)
        {
            ps[index].start_time = max(current_time, ps[index].at);
            total_idle_time += (is_first_process == true) ? 0 : ps[index].start_time - current_time;
            current_time = ps[index].start_time;
            is_first_process = false;
        }
        if (bt_remaining[index] - tq > 0)
        {
            bt_remaining[index] -= tq;
            current_time += tq;
        }
        else
        {
            current_time += bt_remaining[index];
            bt_remaining[index] = 0;
            completed++;

            ps[index].ct = current_time;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].wt = ps[index].tat - ps[index].bt;
            ps[index].rt = ps[index].start_time - ps[index].at;

            sum_tat += ps[index].tat;
            sum_wt += ps[index].wt;
            sum_rt += ps[index].rt;
        }
        // verificamos que procesos necesitan ser pasados a la cola de listo de la lista de entrada
        for (int i = 0; i < n; i++)
        {
            if (bt_remaining[i] > 0 && ps[i].at <= current_time && visited[i] == false)
            {
                q.push(i);
                visited[i] = true;
            }
        }
        // verificamos que procesos que estan en la CPU necesitan ser empujados a la Cola de Listos
        if (bt_remaining[index] > 0)
        {
            q.push(index);
        }
        // Si la cola esta vacia, solo agregamos un proceso de la lista, cuyo tiempo de duracion es mayor a 0
        if (q.empty())
        {
            for (int i = 0; i < n; i++)
            {
                if (bt_remaining[i] > 0)
                {
                    q.push(i);
                    visited[i] = true;
                    break;
                }
            }
        }
    } // Fin del While
    // calculamos el largo del ciclo de finalizacion de los procesos de
    max_completion_time = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        max_completion_time = max(max_completion_time, ps[i].ct);
    }
    length_cycle = max_completion_time - ps[0].at;

    cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;
    // ordenamiento para que el proceso id en el output llegue en el orden original
    sort(ps, ps + n, comparatorPID);
    // output
    cout << "\nPROCESO\tAT\tTIEMPO EN CPU\tCT\tTAT\tWT\tRT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i << "\t\t" << ps[i].at << "\t" << ps[i].bt << "\t\t" << ps[i].ct << "\t" << ps[i].tat << "\t" << ps[i].wt << "\t" << ps[i].rt << endl;
    }
    cout << endl;
    cout << "\nTiempo promedio de respuesta: " << (float)sum_tat / n << endl;
    cout << "Tiempo promedio de espera: " << (float)sum_wt / n << endl;
    cout << "Tiempo promedio de contestacion: " << (float)sum_rt / n << endl;
    cout << "THROUGHPUT: " << n / (float)length_cycle << endl;
    cout << "Porcentaje de CPU utilizado: " << cpu_utilization * 100;
    return 0;
}
