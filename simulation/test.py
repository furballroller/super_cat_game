from scipy.integrate import quad
from scipy.constants import pi

def integrand(x, B,Y):
    return (B*pi*Y)/(2*(x**2+Y**2)**3/2)

result, error = quad(integrand, -1, 1, args=(0.01,0.10))
print(f"Result: {result}, Error: {error}")














def rx_voltage(
    x_coil, y_coil, 
    theta_degs,
    L,             # inductance of "pen" coil
    C,             # capacitance of "pen" cap
    I0_wire1=1.0,  # amplitude of current in wire1
    I0_wire2=1.0,  # amplitude of current in wire2
    freq=50.0,     # frequency in Hz
    N=1,           # number of turns
    area=1e-4,     # coil area in m^2
    mu=mu0         # magnetic permeability of inductor core in (idk)
):
    """
    Returns approximate peak voltage induced in rx loop

    *Gemini says Imax = Vmax * sqrt(C/L) in the "pen"

    Since R >> L, the distance to rx loop is much larger than length of coil,
    B is ~proportional to 1/R^3

    Assuming negligible B-field to the sides of the poles, B is only in direction of coil
    The coil angle applies the same way as the other application, magnetic_flux= sum of (B dot coil_normal)...
    I DON'T CARE ABOUT THE COIL ANGLE :<
    
    """

    
    coilVmax = coil_induced_voltage(x_coil, y_coil, theta_degs, I0_wire1, I0_wire2, freq, N, area) / pow(y_coil,3)

    coilImax = coilVmax * np.sqrt(C/L)

    coil_Bmax = mu * N * coilImax

    #rx_Bmax = coil_Bmax / pow(y_coil, 3)
    rx_phiBmax = coil_Bmax  # REPLACE WITH THE EVALUATED INTEGRAL !!!!!!!!!!!!!!

    rxV = 3




    
    
        
    # # Coil normal direction in the XY plane
    # theta_rads = np.deg2rad(theta_degs)
    # nx = np.cos(theta_rads)
    # ny = np.sin(theta_rads)

    # # Dot product => component of B normal to the coil area
    # Bdotn = Bx_tot*nx + By_tot*ny

    return rxV
