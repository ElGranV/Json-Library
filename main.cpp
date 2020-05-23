#include <iostream>
#include <vector>
#include "json.h"
/*
Créer un fichier utility.h
Ne garder dans le json.h que les fonction utilisables par l'utilisateur
Vérifier la syntaxe du json
Amliorer le constructeur de JsonValue : gérer les objets, et les tableaux
Gérer les exceptions
*/

using namespace std;
using Json::JsonValue;

int main()
{
// Le code suivant est susceptible de lancer des exceptions
// D'où l'intérêt de le placer dans un bloc try/catch
// (elles héritent toutes de la classe std::excpetion

try{

    //L'objet JsonValue constitue un wrapper pour les différents types de données admis en Json
    // Nombre, String, Null, Boolean, Array et Object
    // Dans cette version la valeur "Object" n'a pas encore été implémentée, mais le sera prochainement

    JsonValue nombre(52.0), str("\"Sh*t here we code again\""), nul("null"), boole(true), tableau("[45, \"toi\", true, 100.2]");
    cout << nombre << endl;
    cout << str << endl;
    cout << nul << endl;
    cout << boole << endl;
    cout << "Tableau : " << endl;
    vector<JsonValue> t = tableau;
    for (auto& value : t)
    {
        cout << value << endl;
    }
    cout << tableau << endl;

    cout << 15.2 + (double)nombre; // sans un cast explicite le compilateur renvoie un "ambiguous overload"
    double a = str;


    //Ici on utilise les fonction de lecture/ecriture dans les json
    //Un JsonDict est un dictionaire qui contient les paires clé-valeur d'un objet json
    //On va donc stocker les objets du fichier json dans un tableau (vector) de JsonDict
    //La fonction importJson a deux versions : celle où elle prend en argument un vector<JsonDict>
    // et celle où elle renvoie un vector<JsonDict> (voir json.h)

    vector <Json::JsonDict> objects;

    Json::importJson("data.json", objects);// data.json est supposé exister, la fonction renvoie 'false' dans le cas contraire
    for (auto& dict : objects)
    {
        cout << "{" << endl;
        for (auto& p : dict)
        {
            cout << "\t" << p.first << " : " << p.second.to_string() << endl;
        }
        cout << "}" << endl << endl;
        // cette fonction permet de d'exproter un dctionnaire vers un fichier json
        // pour les arguments voir json.h
        exportObject(dict, "export.json");
    }
}

    catch (exception& e)
    {
        cout << "Exception : " << e.what() << endl;
    }

    getchar();
    return 0;
}
