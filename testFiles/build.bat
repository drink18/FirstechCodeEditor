
FOR %%F in (%cd%\*.src) DO ( 
	p2f %%~nxF -dump par
	p2f %%~nxF
)