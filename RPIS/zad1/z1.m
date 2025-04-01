1;

disp("Rafał Leja 340879 Zadanie 3")

# funkcja gamma eulera
function y = gamma(k)
    if (k == 1/2)
        y = sqrt(pi);
    elseif (k <= 1)
        y = 1;
    else
        y = (k-1)*gamma(k-1);
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
function out = trapezy(a, b, n, func)
	h = (b-a)/n;
	suma = 0;
	for i = 1:n-1
		x = a + i*h;
		suma += func(x);
	end
	out = h/2 * (func(a) + 2*suma + func(b));
end

# metoda romberga
function out = romberg(a, b, n, func)
	R = zeros(n, n);
	for i = 1:n
		R(i, 1) = trapezy(a, b, 2^(i-1), func);
	end
	for j = 2:n
		for i = j:n
			R(i, j) = (4^(j-1) * R(i, j-1) - R(i-1, j-1))/(4^(j-1) - 1);
		end
	end
	out = R(n, n);
end

# dystrybuanta
function out = z1(x, k)
	if x < 0
		out = 0.5 - romberg(x, 0, 13, @(x) f(x, k));
	else
		out = 0.5 + romberg(0, x, 13, @(x) f(x, k));
	end
end


# test całkowania
if romberg(-4, 8, 10, @(x) x) != 24
	error("romberg nie dziala poprawnie");
end

if romberg(-62, 12, 10, @(x) 0.2*x^2 + 5*x) - 6753.76 > 0.01
	error("romberg nie dziala poprawnie");
end

# test gęstości
# wiemy że całka z gęstości musi wynosić 1,
# więc sprawdzamy czy wynik jest bliski 1
if romberg(-100, 100, 10, @(x) f(x, 1)) - 1 > 0.01
	error("f nie dziala poprawnie");
	plot(-100:0.1:100, arrayfun(@(x) f(x, 1), -100:0.1:100));
end