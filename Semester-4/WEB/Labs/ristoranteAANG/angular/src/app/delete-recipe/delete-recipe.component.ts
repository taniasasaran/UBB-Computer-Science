import {Component, OnInit} from '@angular/core';
import {GenericService} from '../generic.service';
import {ActivatedRoute, Router} from '@angular/router';

@Component({
  selector: 'app-delete-recipe',
  templateUrl: './delete-recipe.component.html',
  styleUrls: ['./delete-recipe.component.css']
})
export class DeleteRecipeComponent implements OnInit {

  constructor(private service: GenericService, private router: Router, private route: ActivatedRoute) {
  }

  ngOnInit(): void {
  }

  onYes(): void {
    this.service.deleteRecipe(this.route.snapshot.queryParams['id']).subscribe(() => {
      this.router.navigate(['showRecipes']).then(_ => {
      });
    });
  }

  onNo(): void {
    this.router.navigate(['showRecipes']).then(_ => {
    });
  }

}