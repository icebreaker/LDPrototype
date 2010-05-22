/*! Copyright (c) 2010, Mihail Szabolcs */
/*!
    Simple Billboarding technique.
*/
void main()
{
    //! Identity Matrix
    mat4 lMat = mat4(1.0);
    
    //! X, Y, Z (camera pos)
    lMat[3][0] = gl_ModelViewMatrix[3][0];
    lMat[3][1] = gl_ModelViewMatrix[3][1];
    lMat[3][2] = gl_ModelViewMatrix[3][2];
        
    gl_Position = gl_ProjectionMatrix * lMat * gl_Vertex;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
} 
