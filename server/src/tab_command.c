/*
** tab_command.c for  in /home/clairegizard/PSU/PSU_2015_zappy/server/src
**
** Made by ClaireGizard
** Login   <gizard_a@epitech.net>
**
** Started on  Thu Jun  9 09:26:26 2016 ClaireGizard
** Last update Mon Jun 27 00:48:13 2016 julien
*/

#include <string.h>
#include <stdio.h>
#include "tab_command.h"

t_command	g_tab[]=
  {
    {&avance_cmd, "avance", 7},
    {&droite_cmd, "droite", 7},
    {&gauche_cmd, "gauche", 7},
    {&voir_cmd, "voir", 7},
    {&inventaire_cmd, "inventaire", 1},
    {&prend_obj_cmd, "prend", 7},
    {&pose_obj_cmd, "pose", 7},
    {&expulse_cmd, "expulse", 7},
    {&broadcast_texte_cmd, "broadcast", 7},
    {&incantation_cmd, "incantation", 300},
    {&fork_cmd, "fork", 42},
    {&connect_nbr_cmd, "connect_nbr", 0},
    {NULL, NULL, 0}
  };
