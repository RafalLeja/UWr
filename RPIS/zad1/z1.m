1;

# funkcja gamma eulera
function out = gamma(n)
	out = 1;
	for i = 1:n
		out *= i;
	end
end

# f(x)
function out = f(x, k)
	licz = gamma((k+1)/2);
	mian = sqrt(k*pi) * gamma(k/2);
	mult = 1+((x^2)/k);
	expo = -(k+1)/2;
	out = licz/mian * mult^expo;
end

# metoda trapezow
function out = trapezy(a, b, n, k, func)
	h = (b-a)/n;
	suma = 0;
	for i = 1:n-1
		x = a + i*h;
		suma += func(x, k);
	end
	out = h/2 * (func(a, k) + 2*suma + func(b, k));
end
