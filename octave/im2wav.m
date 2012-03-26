#! /usr/bin/octave -qf

I = imread("inp.png");
x = size(I)(1);
y = size(I)(2);

res = zeros(x * y, 1);

sample_rate = 44100;

I = 1.0 - I(:, :, 1)/255;
I = flipud(I);
R = ifft(I, 1024);

res = reshape(R, size(R)(1) * size(R)(2), 1);

wavwrite(res, sample_rate, 16, "out.wav");
