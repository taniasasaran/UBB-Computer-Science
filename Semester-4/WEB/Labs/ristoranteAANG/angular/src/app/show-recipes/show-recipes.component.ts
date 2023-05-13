import {Component, OnInit} from '@angular/core';
import {GenericService} from '../generic.service';
import {Recipe} from '../recipe';
import {Router} from '@angular/router';

@Component({
  selector: 'app-show-recipes',
  templateUrl: './show-recipes.component.html',
  styleUrls: ['./show-recipes.component.css']
})

export class ShowRecipesComponent implements OnInit {

  recipes: Array<Recipe> = [];

  constructor(private service: GenericService, private router: Router) {
  }

  ngOnInit(): void {
    this.refresh('', '');
  }

  refresh(type: string, name: string): void {
    this.service.fetchRecipes(type, name).subscribe(recipes => this.recipes = recipes);
  }

  navigateToDelete(recipeID: number): void {
    this.router.navigate(['deleteRecipe'], {queryParams: {id: recipeID}}).then(_ => {
    });
  }

  navigateToAdd(): void {
    this.router.navigate(['addRecipe']).then(_ => {
    });
  }

  navigateToUpdate(recipeID: number): void {
    this.router.navigate(['updateRecipe'], {queryParams: {id: recipeID}}).then(_ => {
    });
  }

}
