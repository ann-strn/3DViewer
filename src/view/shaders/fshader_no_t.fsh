varying highp vec4 v_position;
uniform bool edgeLines;
uniform highp vec4 color;

void main(void)
{
//    gl_FragColor = vec4(1.0, 1.0, 1.0 , 1.0);
//        gl_FragColor = color;
//    if (edgeLines)
//        {
//            float dashSize = 0.3;
//            float gapSize = 0.3;
//            float t = mod(gl_FragCoord.x, (dashSize + gapSize)) /
//                    (dashSize + gapSize);
//            if (t > 0.5)
//            {
//                 gl_FragColor = color;
//            }
//            else
//            {
//                discard;
//            }
//        }
//        else
//        {
            gl_FragColor = color;
//        }
}
