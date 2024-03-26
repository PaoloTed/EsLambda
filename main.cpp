#include <iostream>
#include <functional>

//Se ha bisogno di una variabile esterna è necessario  std::function<int(int)> funz1 nel callback
void funzLambda(int *v,std::function<int(int)> funz1) { //std::function<tipo_di_ritorno(tipo_argomento1, tipo_argomento2, ...)>
    for (int i = 0; i < 4; i++) {
        v[i] = funz1(v[i]);
    }
}
//La sintassi per std::function è std::function<tipo_di_ritorno(tipo_argomento1, tipo_argomento2, ...)>.
// Ad esempio, std::function<int(int)>
// rappresenta una funzione che prende un intero come argomento e restituisce un intero.

//std::function è un tipo di dato generale fornito dalla libreria standard di C++
// che può contenere qualsiasi cosa invocabile.
// Questo significa che può contenere
// puntatori a funzione, funzioni membro, funzioni lambda e qualsiasi altra cosa che può essere chiamata come se fosse una funzione.


//Se non ha bisogno di una variabile esterna è possibile usare un puntatore a funzione  int (*funz1)(int) nel callback
void funzPointerFunz(int *v, int (*funz1)(int)) {//int (*funz1)(int) è un puntatore a funzione
    for (int i = 0; i < 4; i++) {
        v[i] = funz1(v[i]);
    }
}
//La sintassi per un puntatore a funzione è tipo_di_ritorno (*nome_funzione)(tipo_argomento1, tipo_argomento2, ...).
// Ad esempio, int (*funz1)(int)
// rappresenta un puntatore a una funzione che prende un intero come argomento e restituisce un intero.


//Esempio d'uso
int main() {
    int x = 5; //variabile esterna che non viene catturata dalla lambda expression
    int k = 1;
    int v1[]{5, 4, 3, 2};
    int v2[] = {5, 4, 3, 2};
    std::cout << "prima della funzione k = " << k << std::endl;


    //[&] prende tutte le variabile esterne per riferimento
    //[=] prende tutte le variabile externe per valore
    //[&k] cattura la variabile k per riferimento, non cattura le altre variabili
    //[=k] cattura la variabile k per valore, non cattura le altre variabili

    //Vaiabile esterna k catturata quindi std::function<int(int)> funz1
    funzLambda(v1, [&k](int val) -> int {
        k++; //catturato quindi usabile
        //x = 10; errore x non è catturato dalla lambda expression
        return k * val;
    });
    std::cout << "Stampa v1 con lambda expression * k incrementato" << std::endl;
    for (int i: v1) {
        std::cout << i << std::endl;
    }
    std::cout << "dopo della funzione k = " << k << std::endl;

    //Vaiabile esterna non catturata quindi int (*funz1)(int)
    funzPointerFunz(v2, [](int val) -> int { return 2 * val; });
    //funzLambda(v2, [](int val) -> int { return 2 * val; }); equivalente alla riga di sopra
    std::cout << "Stampa v2 con punt a funz * 2" << std::endl;
    for (int i: v1) {
        std::cout << i << std::endl;
    }
    return 0;
}
