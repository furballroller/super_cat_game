import numpy as np
from scipy.integrate import quad
from scipy.constants import pi

import matplotlib.pyplot as plt


# Physical constants
mu0 = 4e-7 * pi  # permeability of free space

def single_wire_B(x, y, wire_x, wire_y, I_amp, direction):
    """
    Returns Bx, By at point (x, y) due to a wire carrying current I_amp
    in (+z) if direction=+1, or (-z) if direction=-1.
    Wire is located at (wire_x, wire_y).

    For an infinitely long wire, the magnitude is:
       |B| = mu0 * I / (2*pi*R),
    and the direction is azimuthal around the wire.
    """
    dx = x - wire_x
    dy = y - wire_y
    R2 = dx**2 + dy**2
    if R2 == 0:
        # To avoid singularity, zero out the field near the wire
        return (0.0, 0.0)

    # Magnitude ~ 1/R
    B_mag = mu0 * I_amp / (2*pi*R2)
    # Direction depends on current into/out of the page:
    #   +z => field circles CCW => (Bx, By) = (-dy, +dx) * factor
    #   -z => field circles CW  => (Bx, By) = (+dy, -dx) * factor
    Bx = direction * B_mag * (-dy)
    By = direction * B_mag * ( dx)
    return (Bx, By)

def coil_induced_voltage(
    x_coil, y_coil, 
    theta_degs,
    I0_wire1=1.0,  # amplitude of current in wire1
    I0_wire2=1.0,  # amplitude of current in wire2
    freq=50.0,     # frequency in Hz
    N=1,           # number of turns
    area=1e-4      # coil area in m^2
):
    """
    Returns the amplitude (in volts) of the voltage induced in a small coil.
    The coil normal lies in-plane at angle `theta_degs` from the +x axis.

    Assumptions:
      - The coil is small enough that B is uniform across it.
      - The wires carry AC currents at amplitude I0_wire1, I0_wire2, freq = f.
      - Wire #1 is at (-1,0), current into the page (direction=-1).
      - Wire #2 is at (+1,0), current out of the page (direction=+1).
    """
    omega = 2.0 * pi * freq
    
    # --- B from wire1 (1 A) at coil position ---
    Bx1_1A, By1_1A = single_wire_B(x_coil, y_coil, -1, 0, 1.0, direction=-1)
    # --- B from wire2 (1 A) at coil position ---
    Bx2_1A, By2_1A = single_wire_B(x_coil, y_coil,  1, 0, 1.0, direction=+1)

    # Scale by actual current amplitude in each wire
    Bx_wire1 = Bx1_1A * I0_wire1
    By_wire1 = By1_1A * I0_wire1
    Bx_wire2 = Bx2_1A * I0_wire2
    By_wire2 = By2_1A * I0_wire2

    # Total B at coil center
    Bx_tot = Bx_wire1 + Bx_wire2
    By_tot = By_wire1 + By_wire2

    # Coil normal direction in the XY plane
    theta_rads = np.deg2rad(theta_degs)
    nx = np.cos(theta_rads)
    ny = np.sin(theta_rads)

    # Dot product => component of B normal to the coil area
    Bdotn = Bx_tot*nx + By_tot*ny

    # Flux amplitude (small coil assumption)
    flux_amp = area * Bdotn

    # Induced voltage amplitude = N * dPhi/dt = N * omega * flux_amp
    Vind_amp = N * omega * flux_amp

    return Vind_amp











# FURBALLROLLER WAS HERE
def integrand(x, B,Y):
    return (B*pi*Y)/(2*(x**2+Y**2)**3/2)

def phiB(B, X, Y):
    result, error = quad(integrand, -1-X, 1-X, args=(B,Y))
    
    return result





def rx_voltage(
    x_coil, y_coil, 
    theta_degs,
    L,             # inductance of "pen" coil
    C,             # capacitance of "pen" cap
    f,             # frequency of signal (cycles per second)
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
   rx_phiBmax: Integrate this for between the "infinitely extending" wires at (-1, 0) and (1, 0) when Bmax

    frequency doesn't change? then dphi/dt = d/dt(rx_phiBmax * sin(f*t)) translated horizontally, since frequency is cycles/second
    so rxVmax = rx_phiBmax * f

    Assuming negligible B-field to the sides of the poles, B is only in direction of coil
    The coil angle applies the same way as the other application, magnetic_flux= sum of (B dot coil_normal)...
    I DON'T CARE ABOUT THE COIL ANGLE :<
    
    """

    
    coilVmax = coil_induced_voltage(x_coil, y_coil, theta_degs, I0_wire1, I0_wire2, freq, N, area) / pow(y_coil,3)

    coilImax = coilVmax * np.sqrt(C/L)

    coil_Bmax = mu * N * coilImax

    #rx_Bmax = coil_Bmax / pow(y_coil, 3)
    rx_phiBmax = phiB(coil_Bmax, x_coil, y_coil)  # EVALUATED INTEGRAL !!!!!!!!!!!!!!

    rxVmax = rx_phiBmax * f

    rxV = 3




    
    
        
    # # Coil normal direction in the XY plane
    # theta_rads = np.deg2rad(theta_degs)
    # nx = np.cos(theta_rads)
    # ny = np.sin(theta_rads)

    # # Dot product => component of B normal to the coil area
    # Bdotn = Bx_tot*nx + By_tot*ny

    return rxV

    

















# # Coil parameters
# coil_ypos   = 1         # keep the coil at y=1.5
# coil_theta  = 90        # coil normal at 45 degrees from +x
# coil_area   = 1e-4      # 1 cm^2
# coil_turns  = 10
# freq        = 50.0      # 50 Hz
# I0_1        = -1.0      # amplitude of current in wire1
# I0_2        = -1.0      # amplitude of current in wire2


# # Plot the result
# plt.figure(figsize=(7,5))

# # Sweep x position of the coil
# ypos_values = np.linspace(0.5, 2.5, 5)
# x_values = np.linspace(-5, 5, 200)
# for ypos in ypos_values:
#     voltages = []
#     for x_val in x_values:
#         v_amp = coil_induced_voltage(x_coil=x_val,
#                                         y_coil=ypos,
#                                         theta_degs=coil_theta,
#                                         I0_wire1=I0_1,
#                                         I0_wire2=I0_2,
#                                         freq=freq,
#                                         N=coil_turns,
#                                         area=coil_area)
#         voltages.append(v_amp)

#     # The voltage need to be sent and receive. So we need to square it.
#     voltages = np.array(voltages)**2
#     # Normalize the voltage
#     voltages = voltages / np.max(voltages)
#     plt.plot(x_values, voltages, label=f'y={ypos}')
# plt.xlabel('Coil Center x-position (Normalized)')
# plt.ylabel('Voltage Amplitude (V)')
# plt.title(f'Induced Voltage vs. x-position (theta={coil_theta}°)')
# plt.grid(True)
# plt.legend()
# plt.show()
