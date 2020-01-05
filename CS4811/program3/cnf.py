'''satisfiable.py - a simple Python interface to the zchaff SAT solver.
Originally by Todd Neller
Ported to Python by Dave Musicant
Adapted to course needs by Laura Brown

Copyright (C) 2008 Dave Musicant

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Information about the GNU General Public License is available online at:
http://www.gnu.org/licenses/
To receive a copy of the GNU General Public License, write to the Free
Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.
'''

import os.path
import subprocess
import tempfile

def satisfiable(kb):
    if not os.path.exists('./zchaff'):
        raise RuntimeError('could not locate zchaff executable')

    depth = lambda L: isinstance(L, (list, tuple)) and max(map(depth, L)) + 1
    value = lambda L: all(map(value, L)) if isinstance(L, (list, tuple)) else isinstance(L, (int, long))
    if depth(kb) != 2 or not value(kb):
        raise ValueError("the knowledge base is not in a valid CNF form")

    nvals = lambda L: max([max(l) for l in L])

    out = tempfile.NamedTemporaryFile(mode='w')
    print >> out, 'c This DIMACS format CNF file was generated by cnf.py'
    print >> out, 'c DO NOT EDIT'
    print >> out, 'p cnf', nvals(kb), len(kb)
    for clause in kb:
        for literal in clause:
            print >> out, literal,
        print >> out, '0'
    out.flush()

    process = subprocess.Popen('./zchaff %s' % out.name, stdout=subprocess.PIPE, shell=True)
    process.wait()
    result = process.stdout.read()
    process.stdout.close()
    out.close()

    scan = iter(result.split())
    try:
        while scan.next() != 'RESULT:': pass
        answer = scan.next()
        if answer ==   'SAT': return True
        if answer == 'UNSAT': return False
        raise RuntimeError('neither SAT/UNSAT indicated')
    except StopIteration:
        raise RuntimeError('unexpected file end in generated DIMACS file')

def entails(kb, literal):
    return not satisfiable(kb + [[-literal]])
