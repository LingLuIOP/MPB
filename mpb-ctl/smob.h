/* Copyright (C) 1999, 2000, 2001, 2002, Massachusetts Institute of Technology.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef SMOB_H
#define SMOB_H 1

/* Thanks to Greg Badros for posting a Guile smob tutorial; see
   http://sources.redhat.com/ml/guile/1999-04/msg00107.html */

#define REGISTER_SMOBFUNS(T) \
  do { scm_tc16_smob_ ## T = scm_newsmob(& T ## _smobfuns); } while (0)

#define MAKE_SMOBFUNS(T) \
static scm_smobfuns T ## _smobfuns = { \
  &mark_ ## T, \
  &free_ ## T, \
  &print_ ## T,  0 }

#define NEWCELL_SMOB(ANSWER,T,PSMOB) \
   do { \
     gh_defer_ints(); \
     SCM_NEWCELL((ANSWER)); \
     SCM_SETCAR((ANSWER),scm_tc16_smob_ ## T); \
     SCM_SETCDR((ANSWER),(SCM) (PSMOB)); \
     gh_allow_ints(); \
   } while (0)

/* T_SMOB_P(T, X) is true iff X is an instance of the T SMOB type */
#define T_SMOB_P(T, X) (SCM_NIMP(X) && gh_car(X) == (SCM)scm_tc16_smob_ ## T)

/* T_SMOB(T, X) returns the T * with the guts of the X instance; it
   assumes X is a T SMOB instance, and could crash if it is not */
#define T_SMOB(T, X)  ((T *)(gh_cdr(X)))

/* Since T_SMOB(X) can be dangerous if X is not a T
   object, we also have a SAFE_T_SMOB macro: */
#define SAFE_T_SMOB(T, X) (T_SMOB_P(T,X)?T_SMOB(T,X):NULL)

#endif /* SMOB_H */
