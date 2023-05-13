import {Component, OnInit} from '@angular/core';
import {GenericService} from '../generic.service';
import {Router} from '@angular/router';

@Component({
  selector: 'app-add-recipe',
  templateUrl: './add-recipe.component.html',
  styleUrls: ['./add-recipe.component.css']
})

export class AddRecipeComponent implements OnInit {

  constructor(private service: GenericService, private router: Router) {
  }

  ngOnInit(): void {
  }

  addRecipe(name: string, type: string, author: string, ingredients: string, instructions: string, image: string): void {
    this.service.addRecipe(name, type, author, ingredients, instructions, image).subscribe(() => {
      this.router.navigate(['showRecipes']).then(_ => {
      });
    });
  }

  onCancel(): void {
    this.router.navigate(['showRecipes']).then(_ => {
    });
  }

}
