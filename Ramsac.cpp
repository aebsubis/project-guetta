
#include <boost/lexical_cast.hpp>

#include "Ramsac.h"

Ramsac::Ramsac(GuettaCloud* guettaCloud1, GuettaCloud* guettaCloud2)
{
    this->guettaCloud1 = guettaCloud1;
    this->guettaCloud2 = guettaCloud2;
    this->numPoints = guettaCloud1->data.size();
    menorDistancia = 999;
}

float Ramsac::getDistanciaTotal(GuettaCloud* guettaCloud1, vector<int> indicesGuettaCloud1,GuettaCloud* guettaCloud2, vector<int> indicesGuettaCloud2, GuettaCloud* resultado, Eigen::Matrix4f& transformation_matrix)
{

    estimateRigidTransformationSVD(*guettaCloud1->getPointCloud(), indicesGuettaCloud1, *guettaCloud2->getPointCloud(), indicesGuettaCloud2, transformation_matrix);   
    
   // cout << "Matriz: " << endl << transformation_matrix << endl;

    PointCloud<PointXYZRGB>::Ptr cloud3 (new PointCloud<PointXYZRGB>);
    transformPointCloud (*(guettaCloud1->getPointCloud()), *cloud3, transformation_matrix);
    
       // Creamos el guettaCloud 
    //GuettaCloud* guettaCloud = new GuettaCloud();
    resultado->data.resize(cloud3->points.size());
    for(int i = 0; i < cloud3->points.size(); i++)
    {
        PointXYZRGB point = cloud3->points[i];
        resultado->data[i] = new GuettaKeyPoint(point.x,point.y,point.z,point.r,point.g,point.b,NULL);
        
    }
    
    float distancia = 0;
    // Calculamos la distancia entre los descriptores
    for(int i = 0; i < indicesGuettaCloud1.size(); i++)
    {
        GuettaKeyPoint* p1 = guettaCloud2->data[indicesGuettaCloud1[i]];
        GuettaKeyPoint* p2 = resultado->data[indicesGuettaCloud1[i]];
        float aux = p1->distanceXYZ(p2);
        distancia += aux;
       // cout << "Distancia: " << aux << endl;
    }
   // cout << "Distancia total: " << distancia << endl;    
    return distancia;
}

void Ramsac::compute(int indice, string combinacion)
{
         //   if(combinacion.length() < 6)
        //{
    //if(indice < 4)
    //{
        
        
        if(combinacion.length() >= 5)
        {
            // Calculamos

            vector<int> indices;
            split(combinacion,",",indices);
            
            
                GuettaCloud* resultado = new GuettaCloud();
                Eigen::Matrix4f transformation_matrix;
                float distancia = getDistanciaTotal(guettaCloud2, indices, guettaCloud1, indices, resultado, transformation_matrix);
                cout << indice << " [" << combinacion << "] -> " << distancia << endl;
                if(distancia < menorDistancia)
                {
                    cout << "MENOR: " << indice << " [" << combinacion << "] -> " << distancia << endl;
                   
                    menorDistancia = distancia;
                    mejorCombinacion = indices;
                }
                //cout << indice << " [" << combinacion << "] -> " << distancia << endl;
        }
       
   // cout << indice << " [" << combinacion << "] -> " << endl;
        for(int i = indice; i < numPoints; i++)
        {
            string aux = boost::lexical_cast<string>(i);
            if(combinacion == "")
                compute(i+1, aux);
            else
                compute(i+1, combinacion + "," + aux);
        }
        //    }
    //}
    /*
    cout << indice1 << "," << indice2 << "," << combinacion << endl;
    
    if(indice1 < numPoints)
    {
        string aux = boost::lexical_cast<string>(indice1); 
        compute(indice1+1, indice2, combinacion+aux);
    }
    if(indice2 < numPoints)
    {
        string aux = boost::lexical_cast<string>(indice2); 
        compute(indice1, indice2+1, combinacion+aux);        
    }*/
}

void Ramsac::split(const string& str, const string& delimiters , vector<int>& tokens)
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(atoi(str.substr(lastPos, pos - lastPos).c_str()));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}


int Ramsac::SplitString(const string& input, 
       const string& delimiter, vector<string>& results, 
       bool includeEmpties)
{
    int iPos = 0;
    int newPos = -1;
    int sizeS2 = (int)delimiter.size();
    int isize = (int)input.size();

    if( 
        ( isize == 0 )
        ||
        ( sizeS2 == 0 )
    )
    {
        return 0;
    }

    vector<int> positions;

    newPos = input.find (delimiter, 0);

    if( newPos < 0 )
    { 
        return 0; 
    }

    int numFound = 0;

    while( newPos >= iPos )
    {
        numFound++;
        positions.push_back(newPos);
        iPos = newPos;
        newPos = input.find (delimiter, iPos+sizeS2);
    }

    if( numFound == 0 )
    {
        return 0;
    }

    for( int i=0; i <= (int)positions.size(); ++i )
    {
        string s("");
        if( i == 0 ) 
        { 
            s = input.substr( i, positions[i] ); 
        }
        int offset = positions[i-1] + sizeS2;
        if( offset < isize )
        {
            if( i == positions.size() )
            {
                s = input.substr(offset);
            }
            else if( i > 0 )
            {
                s = input.substr( positions[i-1] + sizeS2, 
                      positions[i] - positions[i-1] - sizeS2 );
            }
        }
        if( includeEmpties || ( s.size() > 0 ) )
        {
            results.push_back(s);
        }
    }
    return numFound;
}