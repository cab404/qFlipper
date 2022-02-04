attribute highp vec4 qt_Vertex;
attribute highp vec2 qt_MultiTexCoord0;

uniform highp mat4 qt_Matrix;
uniform highp float spread;
uniform highp vec2 dirstep;

varying highp vec2 tL7;
varying highp vec2 tL6;
varying highp vec2 tL5;
varying highp vec2 tL4;
varying highp vec2 tL3;
varying highp vec2 tL2;
varying highp vec2 tL1;
varying highp vec2 tL0;
varying highp vec2 tC;
varying highp vec2 tR0;
varying highp vec2 tR1;
varying highp vec2 tR2;
varying highp vec2 tR3;
varying highp vec2 tR4;
varying highp vec2 tR5;
varying highp vec2 tR6;
varying highp vec2 tR7;

void main() {
    gl_Position = qt_Matrix * qt_Vertex;

    tL7 = qt_MultiTexCoord0 + spread * dirstep * float(15.3553);
    tL6 = qt_MultiTexCoord0 + spread * dirstep * float(13.3731);
    tL5 = qt_MultiTexCoord0 + spread * dirstep * float(11.3912);
    tL4 = qt_MultiTexCoord0 + spread * dirstep * float(9.40969);
    tL3 = qt_MultiTexCoord0 + spread * dirstep * float(7.42841);
    tL2 = qt_MultiTexCoord0 + spread * dirstep * float(5.44733);
    tL1 = qt_MultiTexCoord0 + spread * dirstep * float(3.46641);
    tL0 = qt_MultiTexCoord0 + spread * dirstep * float(1.48559);
    tC = qt_MultiTexCoord0;
    tR0 = qt_MultiTexCoord0 + spread * dirstep * float(-1.48559);
    tR1 = qt_MultiTexCoord0 + spread * dirstep * float(-3.46641);
    tR2 = qt_MultiTexCoord0 + spread * dirstep * float(-5.44733);
    tR3 = qt_MultiTexCoord0 + spread * dirstep * float(-7.42841);
    tR4 = qt_MultiTexCoord0 + spread * dirstep * float(-9.40969);
    tR5 = qt_MultiTexCoord0 + spread * dirstep * float(-11.3912);
    tR6 = qt_MultiTexCoord0 + spread * dirstep * float(-13.3731);
    tR7 = qt_MultiTexCoord0 + spread * dirstep * float(-15.3553);
}
