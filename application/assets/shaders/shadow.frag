uniform lowp sampler2D source;
uniform lowp float qt_Opacity;
uniform lowp vec4 color;
uniform lowp float thickness;

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
    gl_FragColor = mix(vec4(0), color, clamp((
                    + float(0.00160725) * texture2D(source, tL7).a
                    + float(0.00485017) * texture2D(source, tL6).a
                    + float(0.0125673) * texture2D(source, tL5).a
                    + float(0.027961) * texture2D(source, tL4).a
                    + float(0.053419) * texture2D(source, tL3).a
                    + float(0.0876354) * texture2D(source, tL2).a
                    + float(0.123456) * texture2D(source, tL1).a
                    + float(0.149346) * texture2D(source, tL0).a
                    + float(0.0783167) * texture2D(source, tC).a
                    + float(0.149346) * texture2D(source, tR0).a
                    + float(0.123456) * texture2D(source, tR1).a
                    + float(0.0876354) * texture2D(source, tR2).a
                    + float(0.053419) * texture2D(source, tR3).a
                    + float(0.027961) * texture2D(source, tR4).a
                    + float(0.0125673) * texture2D(source, tR5).a
                    + float(0.00485017) * texture2D(source, tR6).a
                    + float(0.00160725) * texture2D(source, tR7).a
                   )/thickness, 0.0, 1.0))* qt_Opacity;
}
