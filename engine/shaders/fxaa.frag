#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

uniform sampler2D u_fxaa_tex;

uniform float u_fxaa_sw;
uniform float u_fxaa_sh;
uniform float u_fxaa_threshold;

void main() {
    vec2 texel = vec2(1.0 / u_fxaa_sw, 1.0 / u_fxaa_sh);

    vec3 cN  = texture(u_fxaa_tex, vUV + vec2(0, -texel.y)).rgb;
    vec3 cS  = texture(u_fxaa_tex, vUV + vec2(0,  texel.y)).rgb;
    vec3 cW  = texture(u_fxaa_tex, vUV + vec2(-texel.x, 0)).rgb;
    vec3 cE  = texture(u_fxaa_tex, vUV + vec2( texel.x, 0)).rgb;
    vec3 cM  = texture(u_fxaa_tex, vUV).rgb;
    vec3 cNW = texture(u_fxaa_tex, vUV + vec2(-texel.x, -texel.y)).rgb;
    vec3 cNE = texture(u_fxaa_tex, vUV + vec2( texel.x, -texel.y)).rgb;
    vec3 cSW = texture(u_fxaa_tex, vUV + vec2(-texel.x,  texel.y)).rgb;
    vec3 cSE = texture(u_fxaa_tex, vUV + vec2( texel.x,  texel.y)).rgb;

    float lumaNW = dot(cNW, vec3(0.2126, 0.7152, 0.0722));
    float lumaNE = dot(cNE, vec3(0.2126, 0.7152, 0.0722));
    float lumaSW = dot(cSW, vec3(0.2126, 0.7152, 0.0722));
    float lumaSE = dot(cSE, vec3(0.2126, 0.7152, 0.0722));
    float lumaM  = dot(cM,  vec3(0.2126, 0.7152, 0.0722));

    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

    float range = lumaMax - lumaMin;
    if (range < max(u_fxaa_threshold, lumaMax * 0.125)) {
        fragColor = vec4(cM, 1.0);
        return;
    }

    float lumaN  = dot(cN, vec3(0.2126, 0.7152, 0.0722));
    float lumaS  = dot(cS, vec3(0.2126, 0.7152, 0.0722));
    float lumaW  = dot(cW, vec3(0.2126, 0.7152, 0.0722));
    float lumaE  = dot(cE, vec3(0.2126, 0.7152, 0.0722));

    float edgeVert  = abs(lumaN + lumaS - 2.0 * lumaM) * 2.0;
    float edgeHoriz = abs(lumaW + lumaE - 2.0 * lumaM) * 2.0;
    edgeVert  += abs(lumaNW + lumaSW - 2.0 * lumaN);
    edgeVert  += abs(lumaNE + lumaSE - 2.0 * lumaS);
    edgeHoriz += abs(lumaNW + lumaNE - 2.0 * lumaW);
    edgeHoriz += abs(lumaSW + lumaSE - 2.0 * lumaE);

    bool horizontal = edgeHoriz >= edgeVert;

    float pixel1 = horizontal ? texel.y : texel.x;
    float pixel2 = horizontal ? texel.x : texel.y;

    float luma1 = horizontal ? lumaN : lumaW;
    float luma2 = horizontal ? lumaS : lumaE;

    float gradient1 = abs(luma1 - lumaM);
    float gradient2 = abs(luma2 - lumaM);

    bool isLuma1 = gradient1 >= gradient2;

    float gradientScaled = max(gradient1, gradient2) * 0.25;
    float stepLength = pixel1;

    float lumaLocalAvg = 0.0;
    float pos = 0.0;

    if (isLuma1) {
        lumaLocalAvg = (luma1 + lumaM) * 0.5;
        pos = -stepLength;
    } else {
        lumaLocalAvg = (luma2 + lumaM) * 0.5;
        pos = stepLength;
    }

    vec2 posA = vUV;
    vec2 posB = vUV;
    if (horizontal) {
        posA.y += pos;
        posB.y += pos;
        posA.x -= pixel2 * 0.5;
        posB.x += pixel2 * 0.5;
    } else {
        posA.x += pos;
        posB.x += pos;
        posA.y -= pixel2 * 0.5;
        posB.y += pixel2 * 0.5;
    }

    vec3 colorA = texture(u_fxaa_tex, posA).rgb;
    vec3 colorB = texture(u_fxaa_tex, posB).rgb;
    float lumaPosA = dot(colorA, vec3(0.2126, 0.7152, 0.0722));
    float lumaPosB = dot(colorB, vec3(0.2126, 0.7152, 0.0722));

    float distA = abs(lumaPosA - lumaLocalAvg);
    float distB = abs(lumaPosB - lumaLocalAvg);

    float blend = 0.0;
    if (distA < gradientScaled && distB < gradientScaled) {
        blend = 0.5 - 0.5 * (pos / stepLength);
    } else {
        blend = distA < distB ? -0.5 + 0.5 * (distA / (distA + distB)) :
                                0.5 - 0.5 * (distB / (distA + distB));
    }

    vec2 finalPos = vUV;
    if (horizontal) {
        finalPos.y += blend * stepLength;
    } else {
        finalPos.x += blend * stepLength;
    }

    fragColor = vec4(texture(u_fxaa_tex, finalPos).rgb, 1.0);
}
