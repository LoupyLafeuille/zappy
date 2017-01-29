/*
** init_music.c for  in /home/tran_9/Cours/B4/SysT/zappy/PSU_2015_zappy/server
**
** Made by Sylviane Tran
** Login   <tran_9@epitech.net>
**
** Started on  Thu Jun 23 18:37:28 2016 Sylviane Tran
** Last update Thu Jun 23 18:40:41 2016 Sylviane Tran
*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdlib.h>
#include "map.h"

void			*init_sound(t_item *item)
{
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
  if (!(item->incant = Mix_LoadMUS("./music/SE_03.wav")))
    {
      printf("Cannot load Sound\n");
      return (NULL);
    }
  if (!(item->stone = Mix_LoadMUS("./music/SE_07.wav")))
    {
      printf("Cannot load Sound\n");
      return (NULL);
    }
  return (item);
}
