#version 140
uniform sampler2D texture;
uniform sampler2D texture2;
uniform vec4 ambient;
uniform highp vec4 light_pos;
uniform highp vec4 light_intensity;
uniform highp vec4 material;
uniform int without_texture;
uniform highp mat4 model_prism;
uniform highp mat4 model_L_b1;
uniform highp mat4 model_L_b2;
uniform highp bool shadowed;
uniform int box_numb;
varying highp vec4 texc;
varying highp vec4 pos;
varying highp vec4 normal_for_fs;


float intersect( vec3 origin, vec3 direction, vec3 p0, vec3 p1, vec3 p2 )
{
  vec3 e1 = p1 - p0;
  vec3 e2 = p2 - p0;

  p0 = origin - p0;

  vec3 P = cross( direction , e2 );

  float  det = dot( P , e1 );

  if( det == 0.0 )
    return -1000000.0;

  float u = dot( P , p0 ) / det;

  P = cross( p0 , e1 );

  float w = dot( P , direction ) / det ;

  if( u + w > 1 || w < 0 || u < 0 )
    return 1000000.0;

  return dot( P , e2 ) / det;

}


void main(void)
{ 
/*

        { { +3, -1, -1 }, { -3, -1, -1 }, { -2, +0.73205, -1 }, { +2, +0.73205, -1 } },
        { { +2, +0.73205, -1 }, { -2, +0.73205, -1 }, { -2, +0.73205, +1 }, { +2, +0.73205, +1 } },
        { { +3, -1, +1 }, { +3, -1, -1 }, { +2, +0.73205, -1 }, { +2, +0.73205, +1 } },
        { { -3, -1, -1 }, { -3, -1, +1 }, { -2, +0.73205, +1 }, { -2, +0.73205, -1 } },
        { { +3, -1, +1 }, { -3, -1, +1 }, { -3, -1, -1 }, { +3, -1, -1 } },
        { { -3, -1, +1 }, { +3, -1, +1 }, { +2, +0.73205, +1 }, { -2, +0.73205, +1 } }

*/
//0.366025

vec4 box[36] = vec4[36]
(
/*0*/vec4(-0.5,0.5,-0.5,1),vec4(0.5,0.5,-0.5,1),vec4(-0.5,-0.5,-0.5,1),
/*1*/vec4(-0.5,-0.5,-0.5,1),vec4(0.5,0.5,-0.5,1),vec4(0.5,-0.5,-0.5,1),
/*1*/vec4(-0.5,0.5,0.5,1),vec4(0.5,0.5,0.5,1),vec4(-0.5,-0.5,0.5,1),
/*2*/vec4(-0.5,-0.5,0.5,1),vec4(0.5,0.5,0.5,1),vec4(0.5,-0.5,0.5,1),
/*4*/vec4(-0.5,0.5,0.5,1),vec4(0.5,0.5,0.5,1),vec4(0.5,0.5,-0.5,1),
/*5*/vec4(-0.5,0.5,-0.5,1),vec4(0.5,0.5,-0.5,1),vec4(-0.5,0.5,0.5,1),
/*6*/vec4(-0.5,-0.5,0.5,1),vec4(0.5,-0.5,0.5,1),vec4(0.5,-0.5,-0.5,1),
/*7*/vec4(-0.5,-0.5,-0.5,1),vec4(0.5,-0.5,-0.5,1),vec4(-0.5,-0.5,0.5,1),
/*8*/vec4(0.5,-0.5,0.5,1),vec4(0.5,-0.5,-0.5,1),vec4(0.5,0.5,0.5,1),
/*9*/vec4(0.5,0.5,0.5,1),vec4(0.5,-0.5,-0.5,1),vec4(0.5,0.5,-0.5,1),
/*10*/vec4(-0.5,-0.5,0.5,1),vec4(-0.5,-0.5,-0.5,1),vec4(-0.5,0.5,0.5,1),
/*11*/vec4(-0.5,0.5,0.5,1),vec4(-0.5,-0.5,-0.5,1),vec4(-0.5,0.5,-0.5,1)
);
vec4 prism[24] = vec4[24]
(
/*0*/vec4(-0.5,0.0,0.5,1),vec4(0.5,0.0,0.5,1),vec4(0.0,0.8660250378,0.5,1),
/*1*/vec4(0.5,0.0,-0.5,1),vec4(-0.5,0.0,-0.5,1),vec4(0.0,0.8660250378,-0.5,1),
/*2*/vec4(-0.5,0.0,0.5,1),vec4(-0.5,0.0,-0.5,1),vec4(0.5,0.0,-0.5,1),
/*3*/vec4(-0.5,0.0,0.5,1),vec4(0.5,0.0,-0.5,1),vec4(0.5,0.0,0.5,1),
/*4*/vec4(-0.5,0.0,0.5,1),vec4(0.0,0.8660250378,0.5,1),vec4(0.0,0.8660250378,-0.5,1),
/*5*/vec4(-0.5,0.0,0.5,1),vec4(0.0,0.8660250378,-0.5,1),vec4(-0.5,0.0,-0.5,1),
/*6*/vec4(0.0,0.8660250378,0.5,1),vec4(0.5,0.0,0.5,1),vec4(0.5,0.0,-0.5,1),
/*7*/vec4(0.0,0.8660250378,0.5,1),vec4(0.5,0.0,-0.5,1),vec4(0.0,0.8660250378,-0.5,1)
);



float inters_res;
vec3 p1,p2,p3;
vec4 p_1,p_2,p_3;
bool shadow=false;
vec4 color;
vec4 vec_to_light=light_pos-pos;
vec_to_light.w=0;
float lcos=dot(normalize(vec_to_light),normal_for_fs);
if(lcos<0) lcos=0;
if(without_texture==1) color=vec4(1,1,1,1);
else color=texture2D(texture, texc.st);
//gl_FragColor =color*lcos*light_intensity*material+color*material*ambient;
if(shadowed==true)
{
  {
    //pos=pos+0.01*normalize(vec_to_light);
    vec3 norm,light;
    norm=normal_for_fs.xyz;
    light=normalize(vec_to_light.xyz);
    if(dot(norm,light)>0)
    {
        if(box_numb!=0)
        {
        for(int i=0;i<8;i++)
            {
            p_1=model_prism*prism[i*3];
            p_2=model_prism*prism[i*3+1];
            p_3=model_prism*prism[i*3+2];
            p1=p_1.xyz;
            p2=p_2.xyz;
            p3=p_3.xyz;
            inters_res=intersect(pos.xyz,light,p1,p2,p3);
            if(inters_res!=1000000.0&&inters_res>0)
                  {
                     shadow=true;
                     break;
                  }

            }
        }
/*
        if((shadow==false&&box_numb==2)||(shadow==false&&box_numb==0))
        {
            for(int i=0;i<12;i++)
            {
             p_1=model_L_b1*box[i*3];
             p_2=model_L_b1*box[i*3+1];
             p_3=model_L_b1*box[i*3+2];
             p1=p_1.xyz;
             p2=p_2.xyz;
             p3=p_3.xyz;
             inters_res=intersect(pos.xyz,light,p1,p2,p3);
             if(inters_res!=1000000.0&&inters_res>0)
                {
                    shadow=true;
                    break;
                 }
            }
        }

        if((shadow==false && box_numb==1)||(shadow==false && box_numb==0))
        {
            for(int i=0;i<12;i++)
            {
             p_1=model_L_b2*box[i*3];
             p_2=model_L_b2*box[i*3+1];
             p_3=model_L_b2*box[i*3+2];
             p1=p_1.xyz;
             p2=p_2.xyz;
             p3=p_3.xyz;
             inters_res=intersect(pos.xyz,light,p1,p2,p3);
             if(inters_res!=1000000.0&&inters_res>0)
                {
                    shadow=true;
                    break;
                 }
            }
        }
        */
    }
    if(shadow)
        gl_FragColor=color*material*vec4(0.2,0.2,0.2,1);
    else
        gl_FragColor =color*lcos*light_intensity*material+color*material*ambient;
  }
}
else
    gl_FragColor =color*lcos*light_intensity*material+color*material*ambient;
}
