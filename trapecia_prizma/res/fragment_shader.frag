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
varying highp vec4 texc;
varying highp vec4 pos;
varying highp vec4 normal_for_fs;

vec4 box[36]=
{
/*0*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*1*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*2*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*3*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*4*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*5*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*6*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*7*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*8*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*9*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*10*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*11*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
};

vec4 prism[24]=
{
/*0*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*1*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*2*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*3*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*4*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*5*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*6*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
/*7*/vec4(1,1,1,1),vec4(1,1,1,1),vec4(1,1,1,1),
};

float intersect( vec4 origin, vec4 direction, vec4 p0, vec4 p1, vec4 p2 )
{

vec4 e1 = p1 - p0;
vec4 e2 = p2 - p0;

p0 = origin - p0;

vec4 P = cross( direction , e2 );

float  det = dot( P , e1 );

if( det == 0.0 )
return -1000000;

float u = dot( P , p0 ) / det;

P = cross( p0 , e1 );

float w = dot( P , direction ) / det ;

if( u + w > 1 || w < 0 || u < 0 )
return 1000000;

return dot( P , e2 ) / det;


}

void main(void)
{
                //prism[0]=vec4(0,0,0,0);
vec4 color;
vec4 vec_to_light=light_pos-pos;
vec_to_light.w=0;
float lcos=dot(normalize(vec_to_light),normal_for_fs);
if(lcos<0) lcos=0;
if(without_texture==1) color=vec4(1,1,1,1);
else color=texture2D(texture, texc.st);
gl_FragColor =color*lcos*light_intensity*material+color*material*ambient;
 //gl_FragColor=0;
}
