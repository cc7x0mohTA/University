
function bairstow(a, n)

	b  = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
	bp = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
	bq = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]

	p = 0.0
	q = 0.0
	eps = 0.00000000000000000001

	for iter = 1:100000

		i = n+1

		while i >= 2
			b[i] = a[i] - p*b[i+1] - q*b[i+2]
			i = i - 1
		end

		b[1] = a[1] - q*b[3]

		i = n+1

		while i >= 2
			bp[i] = -b[i+1] - p*bp[i+1] - q*bp[i+2];
			bq[i] = -p*bq[i+1] - b[i+2] - q*bq[i+2];
			i = i - 1
		end

		bp[1] = -q*bp[3]
		bq[1] = -q*bq[3] - b[3]
		dn = bp[1]*bq[2] - bp[2]*bq[1]
		dp = (b[1]*bq[2] - b[2]*bq[1])/dn
		p = p - dp
		dq = (b[2]*bp[1] - b[1]*bp[2])/dn
		q = q - dq

		if abs(dq) + abs(dp) <= eps
			break
		end
	end

	print("\n------------------------------------------------------\n")
	print("p= ", p, " ", q, " \n")
	print("Czynnik kwadratowy = x^2+(", p, " x)+(", q, ") \n")
	print("\nPierwiastki (roboczo): \n")

	zz = p*p - 4*q

	if zz >= 0
  		rt = sqrt(zz)
  		print( (-p+rt)/2, " ", (-p-rt)/2, "\n")
  	else
  		rt=sqrt(-zz)
  		print(-p/2, " + ", rt/2, "i\n")
  		print(-p/2, " + ", rt/2, "i\n")
  	end

  	print("\nWspolczynniki wielomianu ktory pozostal \n")

  	for j = 3:(n+1)
  		print(j-2, " ", b[j], "\n")
  	end

end

