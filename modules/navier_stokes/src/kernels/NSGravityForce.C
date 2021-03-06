/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "NSGravityForce.h"

template<>
InputParameters validParams<NSGravityForce>()
{
  InputParameters params = validParams<NSKernel>();
  params.addClassDescription("This class computes the gravity force contribution.");
  // The strength of the acceleration in the _component direction.  Make this
  // value negative if you want force in the -_component direction.
  params.addRequiredParam<Real>("acceleration", "The body force vector component.");
  return params;
}

NSGravityForce::NSGravityForce(const InputParameters & parameters) :
    NSKernel(parameters),
    _acceleration(getParam<Real>("acceleration"))
{
}

Real
NSGravityForce::computeQpResidual()
{
  // -rho * g * phi
  return -_rho[_qp] * _acceleration * _test[_i][_qp];
}

Real NSGravityForce::computeQpJacobian()
{
  return 0.0;
}

Real
NSGravityForce::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _rho_var_number)
    return -_phi[_j][_qp] * _acceleration * _test[_i][_qp];

  return 0.0;
}
